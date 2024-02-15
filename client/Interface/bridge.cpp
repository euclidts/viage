#include <QDesktopServices>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <wobjectimpl.h>

#include "bridge.hpp"
#include "netManager.hpp"
#include <client.hpp>
#include <client_utils.hpp>
#include <Item/c_account.hpp>
#include <Item/c_owner.hpp>
#include <Item/c_contact.hpp>
#include <Item/c_company.hpp>
#include <Item/c_team.hpp>
#include <Item/c_senior_citizen.hpp>
#include <c_list.hpp>
#include <Model/list_model.hpp>
#include <account_filter_model.hpp>
#include <user_filter_model.hpp>
#include <document_filter_model.hpp>

using namespace client_utils;
using namespace Json;

namespace Interface
{
W_OBJECT_IMPL(bridge)

bridge& bridge::instance()
{
    static bridge instance;
    return instance;
}

void bridge::init()
{
    engine = new QQmlApplicationEngine{};
}

QQmlContext* bridge::context()
{
    return engine->rootContext();
}

void bridge::registerQml()
{
    using namespace Data;
    using namespace People;

    // calculator
    qmlRegisterType<list_model<c_senior_citizen>>("People", 1, 0, "SeniorCitizenModel");

    // accounts
    accountModel = new list_model<c_account>{};
    accountModel->setList(client::instance().get_accounts());

    accountFilter = new account_filter_model{accountModel};
    qmlRegisterUncreatableType<account_filter_model>("Data", 1, 0, "AccountModel", "");
    context()->setContextProperty("accountModel", accountFilter);

    // owners
    qmlRegisterType<list_model<c_owner>>("People", 1, 0, "OwnersModel");

    // contacts
    qmlRegisterType<list_model<c_contact>>("People", 1, 0, "ContactModel");

    // documents
    qmlRegisterType<list_model<c_document>>("Data", 1, 0, "DocumentModel");
    qmlRegisterType<document_filter_model>("Data", 1, 0, "DocumentFilterModel");

    // users
    userModel = new list_model<c_user>{};
    userModel->setList(client::instance().get_users());

    userFilter = new user_filter_model{userModel};
    selectedUser = new user_filter_model{userModel, true};
    qmlRegisterUncreatableType<user_filter_model>("People", 1, 0, "UserModel", "");
    context()->setContextProperty("userModel", userFilter);
    context()->setContextProperty("selectedUser", selectedUser);

    // companies
    qmlRegisterType<list_model<c_company>>("Data", 1, 0, "CompaniesModel");

    // teams
    qmlRegisterType<list_model<c_team>>("Data", 1, 0, "TeamsModel");

    // Hiering
    connect(this,
            &bridge::requestUser,
            selectedUser,
            &user_filter_model::forceFilterRole);

    connect(&Interface::netManager::instance(),
            &netManager::loggedIn,
            this,
            &bridge::onLogin);

    connect(&Interface::netManager::instance(),
            &netManager::replyError,
            this,
            &bridge::onException);

    connect(&Interface::netManager::instance(),
            &netManager::userChanged,
            this,
            &bridge::setUserId);

    connect(&Interface::netManager::instance(),
            &netManager::clearanceChanged,
            this,
            &bridge::setClearance);

    using namespace Data;

    connect(client::instance().get_accounts(),
            &c_list<c_account>::postItemsAppended,
            this,
            [this]()
    {
        if (onboarding)
        {
            onboarding = false;
            setAccoountId(client::instance().get_accounts()->items().constLast().id);
            setAccountState(0);
            emit preOnboarding(accountId);
        }
    });

    connect(client::instance().get_accounts(),
            &c_list<c_account>::dataChangedAt,
            this,
            [this] (int index)
    {
        const auto item{client::instance().get_accounts()->item_at_id(accountId)};

        setAccountState(item.state);
        setPPE(item.ppe);
        setAccountReceived(to_QDateTime(item.receivedDate).date());
        setAccountTransmited(to_QDateTime(item.transmitedDate).date());
        setAccountExpertized(to_QDateTime(item.expertizedDate).date());
        setAccountNotarized(to_QDateTime(item.notarizedDate).date());
        setAccountDecided(to_QDateTime(item.decidedDate).date());
        setAccountPaid(to_QDateTime(item.paidDate).date());
    });

    connect(client::instance().get_documents(),
            &c_list<c_document>::loaded,
            this,
            &bridge::check_doc_completion);

    connect(client::instance().get_documents(),
            &c_list<c_document>::dataChangedAt,
            this,
            &bridge::upload_doc);

    connect(client::instance().get_documents(),
            &c_list<c_document>::postItemsRemoved,
            this,
            &bridge::check_doc_completion);

    connect(client::instance().get_documents(),
            &c_list<c_document>::validate,
            this,
            &bridge::cleanup_docs);

    using namespace People;

    connect(client::instance().get_users(),
            &c_list<c_user>::postItemsAppended,
            this,
            [this]()
    {
        if (hiring)
        {
            hiring = false;
            emit requestUser(client::instance().get_users()->items().constLast().id);
            emit loaded();
        }
    });

    qmlRegisterUncreatableType<bridge>("Interface", 1, 0, "Bridge", "");
    context()->setContextProperty("bridge", this);
}

void bridge::onLogin(bool success, const QString &errorString) const
{
    QMetaObject::invokeMethod(qmlObject,
                              "onLogin",
                              Q_ARG(bool, success),
                              Q_ARG(QString, errorString));
}

void bridge::onException(const QString &prefix, const QString &errorString) const
{
    QMetaObject::invokeMethod(qmlObject,
                              "onException",
                              Q_ARG(QString, prefix),
                              Q_ARG(QString, errorString));
}

void bridge::authenticate(const QString &username, const QString &password) const
{
    Interface::netManager::instance().authenticate(username, password);
}

void bridge::downloadFile(const QString &key, const QUrl &directory, const QString &fileName) const
{
    Interface::netManager::instance().downloadFile(key.toStdString().c_str(),
                      filePath(directory, fileName),
                      [this] (bool success, const QString& string)
    {
        if (!success) onException("downloadFile error", string);
    });
}

void bridge::requestReport()
{
    setDownloadProgress(0.f);

    Interface::netManager::instance().downloadFile("export/accounts",
                      client::get_tempPath() + "/Viage.xlsx",
                      [this] (bool success, const QString& error)
    {
        if (success)
        {
            if (!QDesktopServices::openUrl(client::get_tempPath() + "/Viage.xlsx"))
                onException("requestReport error", "QDesktopervices : could not open excel");
            else
                emit loaded();
        }
        else
            onException("requestReport error", error);

        setDownloadProgress(-1.f);
    },
    [this](qint64 byteSent, qint64 totalbytes)
    {
        setDownloadProgress((byteSent / 1024.) / (totalbytes / 1024.));
        qDebug() << (byteSent / 1024.) / (totalbytes / 1024.);
    });
}

void bridge::requestAccount()
{
    std::string str{"accounts/"};
    str.append(std::to_string(accountId));
    str.append("/pdf");

    QString path{client::get_tempPath()};
    path.append('/');
    path.append(QString::number(accountId));
    path.append(".pdf");

    setDownloadProgress(0.f);

    Interface::netManager::instance().downloadFile(str.c_str(),
                      path,
                      [this, path] (bool success, const QString& error)
    {
        if (success)
        {
            if (!QDesktopServices::openUrl(path))
                onException("requestAccount error", "QDesktopervices : could not open pdf");
            else
                emit loaded();
        }
        else
            onException("requestAccount error", error);

        setDownloadProgress(-1.f);
    },
    [this](qint64 byteSent, qint64 totalbytes)
    {
        setDownloadProgress((byteSent / 1024.) / (totalbytes / 1024.));
        qDebug() << (byteSent / 1024.) / (totalbytes / 1024.);
    });
}

using namespace Json;

void bridge::requestEmail()
{
    std::string str{"accounts/"};
    str.append(std::to_string(accountId));
    str.append("/email");

    std::string params{"&forceRefreshPdf=True"};

    Interface::netManager::instance().getFromKey(str.c_str(),
                    [this] (const QByteArray& rep)
    {
        Value json;
        Reader reader;
        reader.parse(rep.toStdString(), json);

        if (json.isMember("success"))
            if (!json["success"].asBool())
                onException("requestAccount error",
                            QString::fromStdString(json["errorString"].asString()));
    },
    params.c_str());
}

void bridge::updatePwd(const QString& newPwd) const
{
    Value json;
    json["password"] = newPwd.toStdString();

    changePwd("changePassword", json);
}

void bridge::resetPwd(int id) const
{
    Value json;
    json["id"] = id;

    changePwd("resetPassword", json);
}

void bridge::changePwd(const char *key, const Value& json) const
{
    Interface::netManager::instance().putToKey(key,
                  to_QByteArray(json),
                  [this] (const Value& rep)
    { emit loaded(); },
    "changePwd error");
}

void bridge::lockUser(int id, bool locked) const
{
    Value json;
    json["id"] = id;
    json["lock"] = locked;

    Interface::netManager::instance().putToKey("lock",
                  to_QByteArray(json),
                  [this] (const Value& rep)
    { emit loaded(); },
    "loackUser error");
}

void bridge::getAccountDates() const
{
    std::string key{"accountState/"};
    key.append(std::to_string(accountId));

    Interface::netManager::instance().getFromKey(key.c_str(),
                    [this] (const QByteArray& rep)
    {
        Value json;
        Reader reader;
        reader.parse(rep.toStdString(), json);

        if (!json.isMember("state") && !json.isMember("accountState"))
        {
            emit Interface::netManager::instance().replyError("getAccountDates error");
            return;
        }

        auto account{client::instance().get_accounts()->item_at_id(accountId)};
        account.read(json);
        client::instance().get_accounts()->setItemAtId(accountId, account);
        emit loaded();
    });
}

void bridge::updateState(int newState) const
{
    Json::Value json;
    json["id"] = accountId;
    json["state"] = accountState + newState;

    Interface::netManager::instance().putToKey("accountState",
                  to_QByteArray(json),
                  [this] (const Value& rep)
    {
        auto account{client::instance().get_accounts()->item_at_id(accountId)};
        account.read(rep);
        client::instance().get_accounts()->setItemAtId(accountId, account);
        emit loaded();
    },
    "updateState error");
}

void bridge::updatePPE() const
{
    Json::Value json;
    json["id"] = accountId;
    json["isPPE"] = !ppe;

    Interface::netManager::instance().putToKey("accountPPE",
                  to_QByteArray(json),
                  [this] (const Value& rep)
    {
        auto account{client::instance().get_accounts()->item_at_id(accountId)};
        account.read(rep);
        client::instance().get_accounts()->setItemAtId(accountId, account);
        emit loaded();
    },
    "updatePPE error");
}

void bridge::sendOnboardedEmail() const
{
    std::string str{"accounts/"};
    str.append(std::to_string(accountId));
    str.append("/email");
    Interface::netManager::instance().getFromKey(str.c_str(),
                    [this](const QByteArray& rep)
    { emit loaded(); });
}

QUrl bridge::getPictureName(QString name, int index) const
{
    return QUrl::fromLocalFile(client::get_tempPath()
                               + '/'
                               + QString::number(accountId)
                               + '_'
                               + name.replace(' ', '_').replace('/', '-')
                               + '_'
                               + QString::number(index + 1)
                               + ".jpeg");
}

Data::People::user_item::clearances bridge::getClearance() const
{
    return clearance;
}

void bridge::setClearance(int newClearance)
{
    if (clearance == newClearance)
        return;
    clearance = Data::People::user_item::clearances(newClearance);
    emit clearanceChanged();
}

int bridge::getAccountId() const
{
    return accountId;
}

void bridge::setAccoountId(int newAccountId)
{
    if (accountId == newAccountId)
        return;
    accountId = newAccountId;
    emit accountIdChanged();
}

int bridge::getAccountState() const
{
    return accountState;
}

void bridge::setAccountState(int newAccountState)
{
    if (accountState == newAccountState)
        return;
    accountState = newAccountState;
    emit accountStateChanged();
}

bool bridge::getPPE() const
{
    return ppe;
}

void bridge::setPPE(bool newPPE)
{
    if (ppe == newPPE)
        return;
    ppe = newPPE;
    emit ppeChanged();
}

bool bridge::getDocumentsCompleted() const
{
    return documentsCompleted;
}

void bridge::setDocumentsCompleted(bool newDocumentsCompleted)
{
    if (documentsCompleted == newDocumentsCompleted)
        return;
    documentsCompleted = newDocumentsCompleted;
    emit documentsCompletedChanged();
}

void bridge::check_doc_completion()
{
    using namespace Data;
    setDocumentsCompleted(document_item::documents_completed(client::instance().get_documents()->get_list(), ppe));
}

void bridge::cleanup_docs(int ai)
{
    bool update_parent{false};

    for (const auto& doc : client::instance().get_documents()->items())
    {
        if (doc.category == Data::document_item::None)
        {
            // clean orphan documents
            client::instance().get_documents()->remove(doc.id);
            update_parent = true;
        }
    }

    if (update_parent)
    {
        auto account{client::instance().get_accounts()->item_at_id(ai)};

        if (account.update(client::instance().get_documents()))
            client::instance().get_accounts()->setItemAtId(ai, account);
    }

    emit loaded();
}

void bridge::upload_doc(int index)
{
    auto doc{client::instance().get_documents()->item_at(index)};

    if (doc.state != Data::document_item::NotUploded || doc.localPath.empty())
        return;

    QFile file{doc.localPath};
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly))
            onException("upload_doc error", file.errorString());
        else
        {
            const auto bytes{file.readAll()};
            const auto body{QString(bytes.toBase64())};

            Value json;
            doc.write(json);
            json["body"] = body.toStdString();

            int parent_account{accountId};

            Interface::netManager::instance().putToKey(client::instance().get_documents()->key,
                          to_QByteArray(json),
                          [this, parent_account, doc]
                          (const Value& rep)
                          mutable {
                auto updated_account{client::instance().get_accounts()->item_at_id(parent_account)};

                if (rep.isMember("document") && rep["document"].isObject())
                {
                    doc.read(rep["document"]);
                    client::instance().get_documents()->setItemAtId(doc.id, doc);
                }

                if (rep.isMember("accountState") && rep["accountState"].isInt())
                {
                    updated_account.state = Data::account_item::states(rep["accountState"].asInt());
                    updated_account.update(client::instance().get_documents());
                    client::instance().get_accounts()->setItemAtId(parent_account, updated_account);
                }

                check_doc_completion();
            },
            "upload_doc error",
            [this](){},
            [this, doc](qint64 byteSent, qint64 totalbytes)
            mutable {
                if (byteSent == 0)
                    return;

                if (doc.state != Data::document_item::Uploading)
                    doc.state = Data::document_item::Uploading;

                doc.uploadProgress = (byteSent / 1024.) / (totalbytes / 1024.);
                client::instance().get_documents()->setItemAtId(doc.id, doc);
            });
        }
    }
    else
    { onException("upload_doc error", "Fichier introuvable"); }
}

void bridge::setDownloadProgress(float newDownloadProgress)
{
    downloadProgress = newDownloadProgress;
    emit downloadProgressChanged();
}

float bridge::getDownloadProgress() const
{
    return downloadProgress;
}

const QDate &bridge::getAccountDecided() const
{
    return accountDecided;
}

void bridge::setAccountDecided(const QDate &newAccountDecided)
{
    if (accountDecided == newAccountDecided)
        return;
    accountDecided = newAccountDecided;
    emit accountDecidedChanged();
}

const QDate &bridge::getAccountReceived() const
{
    return accountReceived;
}

void bridge::setAccountReceived(const QDate &newAccountReceived)
{
    if (accountReceived == newAccountReceived)
        return;
    accountReceived = newAccountReceived;
    emit accountReceivedChanged();
}

const QDate &bridge::getAccountTransmited() const
{
    return accountTransmited;
}

void bridge::setAccountTransmited(const QDate &newAccountTransmited)
{
    if (accountTransmited == newAccountTransmited)
        return;
    accountTransmited = newAccountTransmited;
    emit accountTransmitedChanged();
}

const QDate &bridge::getAccountExpertized() const
{
    return accountExpertized;
}

void bridge::setAccountExpertized(const QDate &newAccountExpertized)
{
    if (accountExpertized == newAccountExpertized)
        return;
    accountExpertized = newAccountExpertized;
    emit accountExpertizedChanged();
}

const QDate &bridge::getAccountNotarized() const
{
    return accountNotarized;
}

void bridge::setAccountNotarized(const QDate &newAccountNotarized)
{
    if (accountNotarized == newAccountNotarized)
        return;
    accountNotarized = newAccountNotarized;
    emit accountNotarizedChanged();
}

const QDate &bridge::getAccountPaid() const
{
    return accountPaid;
}

void bridge::setAccountPaid(const QDate &newAccountPaid)
{
    if (accountPaid == newAccountPaid)
        return;
    accountPaid = newAccountPaid;
    emit accountPaidChanged();
}

int bridge::getUserId() const
{
    return userId;
}

void bridge::setUserId(int newUserId)
{
    if (userId == newUserId)
        return;
    userId = newUserId;
    emit userIdChanged();
}

bool bridge::hasFlag(int value, int flag) const noexcept
{
    return value & flag;
}

bool bridge::accountHasFlag(int flag) const noexcept
{
    return hasFlag(accountState, flag);
}

const QString bridge::filePath(const QUrl &directory, const QString &fileName) const
{
    auto filePath{directory.path()};
    filePath.append('/');
    filePath.append(fileName);

    const auto fullPath{QUrl::fromLocalFile(filePath)};

    return fullPath.toLocalFile();
}

void bridge::onboard()
{
    onboarding = true;
    client::instance().get_accounts()->add();
}

void bridge::hire()
{
    hiring = true;
    client::instance().get_users()->add();
}

}
