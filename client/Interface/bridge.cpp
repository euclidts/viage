#include <QDesktopServices>

#include <wobjectimpl.h>

#include "bridge.hpp"
#include <utils.hpp>
#include <Item/c_account.hpp>
#include <c_list.hpp>

using namespace Utils;

namespace Interface
{
W_OBJECT_IMPL(bridge)

bridge::bridge(Interface::netManager* manager,
               Data::c_list<Data::People::c_user>* users,
               Data::c_list<Data::c_account>* accounts,
               Data::c_list<Data::c_document>* documents,
               const QString& tempPath)
    : mng{manager}
    , usrs{users}
    , acnts{accounts}
    , docs{documents}
    , rootPath{tempPath}
{
    connect(mng, &netManager::loggedIn,
            this, &bridge::onLogin);

    connect(mng, &netManager::replyError,
            this, &bridge::onException);

    connect(mng, &netManager::userChanged,
            this, &bridge::setUserId);

    connect(mng, &netManager::clearanceChanged,
            this, &bridge::setClearance);

    using namespace Data;

    connect(acnts, &c_list<c_account>::postItemsAppended,
            this, [this]()
    {
        if (onboarding)
        {
            onboarding = false;
            setAccoountId(acnts->items().constLast().id);
            setAccountState(0);
            emit preOnboarding(accountId);
        }
    });

    connect(acnts, &c_list<c_account>::dataChangedAt,
            this, [this] (int index)
    {
        const auto item{acnts->item_at_id(accountId)};

        setAccountState(item.state);
        setPPE(item.ppe);
        setAccountReceived(to_QDateTime(item.receivedDate).date());
        setAccountTransmited(to_QDateTime(item.transmitedDate).date());
        setAccountExpertized(to_QDateTime(item.expertizedDate).date());
        setAccountNotarized(to_QDateTime(item.notarizedDate).date());
        setAccountDecided(to_QDateTime(item.decidedDate).date());
        setAccountPaid(to_QDateTime(item.paidDate).date());
    });

    connect(docs, &c_list<c_document>::loaded,
            this, &bridge::check_doc_completion);

    connect(docs, &c_list<c_document>::dataChangedAt,
            this, &bridge::upload_doc);

    connect(docs, &c_list<c_document>::postItemsRemoved,
            this, &bridge::check_doc_completion);

    connect(docs, &c_list<c_document>::validate,
            this, &bridge::cleanup_docs);

    using namespace People;

    connect(usrs, &c_list<c_user>::postItemsAppended,
            this, [this]()
    {
        if (hiring)
        {
            hiring = false;
            emit requestUser(usrs->items().constLast().id);
            emit loaded();
        }
    });
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
    mng->authenticate(username, password);
}

void bridge::downloadFile(const QString &key, const QUrl &directory, const QString &fileName) const
{
    mng->downloadFile(key.toStdString().c_str(),
                      filePath(directory, fileName),
                      [this] (bool success, const QString& string)
    {
        if (!success) onException("downloadFile error", string);
    });
}

void bridge::requestReport()
{
    setDownloadProgress(0.f);

    mng->downloadFile("export/accounts",
                      rootPath + "/Viage.xlsx",
                      [this] (bool success, const QString& error)
    {
        if (success)
        {
            if (!QDesktopServices::openUrl(rootPath + "/Viage.xlsx"))
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

    QString path{rootPath};
    path.append('/');
    path.append(QString::number(accountId));
    path.append(".pdf");

    setDownloadProgress(0.f);

    mng->downloadFile(str.c_str(),
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

    mng->getFromKey(str.c_str(),
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
    mng->putToKey(key,
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

    mng->putToKey("lock",
                  to_QByteArray(json),
                  [this] (const Value& rep)
    { emit loaded(); },
    "loackUser error");
}

void bridge::getAccountDates() const
{
    std::string key{"accountState/"};
    key.append(std::to_string(accountId));

    mng->getFromKey(key.c_str(),
                    [this] (const QByteArray& rep)
    {
        Value json;
        Reader reader;
        reader.parse(rep.toStdString(), json);

        if (!json.isMember("state") && !json.isMember("accountState"))
        {
            emit mng->replyError("getAccountDates error");
            return;
        }

        auto account{acnts->item_at_id(accountId)};
        account.read(json);
        acnts->setItemAtId(accountId, account);
        emit loaded();
    });
}

void bridge::updateState(int newState) const
{
    Json::Value json;
    json["id"] = accountId;
    json["state"] = accountState + newState;

    mng->putToKey("accountState",
                  to_QByteArray(json),
                  [this] (const Value& rep)
    {
        auto account{acnts->item_at_id(accountId)};
        account.read(rep);
        acnts->setItemAtId(accountId, account);
        emit loaded();
    },
    "updateState error");
}

void bridge::updatePPE() const
{
    Json::Value json;
    json["id"] = accountId;
    json["isPPE"] = !ppe;

    mng->putToKey("accountPPE",
                  to_QByteArray(json),
                  [this] (const Value& rep)
    {
        auto account{acnts->item_at_id(accountId)};
        account.read(rep);
        acnts->setItemAtId(accountId, account);
        emit loaded();
    },
    "updatePPE error");
}

void bridge::sendOnboardedEmail() const
{
    std::string str{"accounts/"};
    str.append(std::to_string(accountId));
    str.append("/email");
    mng->getFromKey(str.c_str(),
                    [this](const QByteArray& rep)
    { emit loaded(); });
}

QUrl bridge::getPictureName(QString name, int index) const
{
    return QUrl::fromLocalFile(rootPath
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
    setDocumentsCompleted(document_item::documents_completed(docs->get_list(), ppe));
}

void bridge::cleanup_docs(int ai)
{
    bool update_parent{false};

    for (const auto& doc : docs->items())
    {
        if (doc.category == Data::document_item::None)
        {
            // clean orphan documents
            docs->remove(doc.id);
            update_parent = true;
        }
    }

    if (update_parent)
    {
        auto account{acnts->item_at_id(ai)};

        if (account.update(docs))
            acnts->setItemAtId(ai, account);
    }

    emit loaded();
}

void bridge::upload_doc(int index)
{
    auto doc{docs->item_at(index)};

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

            mng->putToKey(docs->key,
                          to_QByteArray(json),
                          [this, parent_account, doc]
                          (const Value& rep)
                          mutable {
                auto updated_account{acnts->item_at_id(parent_account)};

                if (rep.isMember("document") && rep["document"].isObject())
                {
                    doc.read(rep["document"]);
                    docs->setItemAtId(doc.id, doc);
                }

                if (rep.isMember("accountState") && rep["accountState"].isInt())
                {
                    updated_account.state = Data::account_item::states(rep["accountState"].asInt());
                    updated_account.update(docs);
                    acnts->setItemAtId(parent_account, updated_account);
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
                docs->setItemAtId(doc.id, doc);
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
    acnts->add();
}

void bridge::hire()
{
    hiring = true;
    usrs->add();
}

}
