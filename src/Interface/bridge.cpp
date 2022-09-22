#include <QDesktopServices>

#include <wobjectimpl.h>

#include "bridge.hpp"
#include <Items/document_item.hpp>
#include <Items/account_item.hpp>
#include <Lists/item_list.hpp>

namespace Interface
{
W_OBJECT_IMPL(bridge)

bridge::bridge(Interface::netManager* manager,
               Data::item_list<Data::People::user_item>* users,
               Data::item_list<Data::account_item>* accounts,
               Data::item_list<Data::document_item>* documents,
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

    connect(acnts, &item_list<account_item>::postItemsAppended,
            this, [this]()
    {
        if (onboarding)
        {
            onboarding = false;
            setAccoountId(acnts->items().constLast().id);
            setAccountState(0);
            emit requestOwners(accountId);
        }
    });

    connect(acnts, &item_list<account_item>::dataChangedAt,
            this, [this] (int index)
    {
        const auto item{acnts->item_at_id(accountId)};

        setAccountState(item.state);
        setAccountReceived(item.receivedDate);
        setAccountExpertized(item.expertizedDate);
        setAccountNotarized(item.notarizedDate);
        setAccountDecided(item.decidedDate);
        setAccountPaid(item.paidDate);
    });

    connect(docs, &item_list<document_item>::loaded,
            this, &bridge::check_doc_completion);

    connect(docs, &item_list<document_item>::dataChangedAt,
            this, &bridge::upload_doc);

    connect(docs, &item_list<document_item>::postItemsRemoved,
            this, &bridge::check_doc_completion);

    connect(docs, &item_list<document_item>::validate,
            this, &bridge::cleanup_docs);

    using namespace People;

    connect(usrs, &item_list<user_item>::postItemsAppended,
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

void bridge::onLogin(const bool& success, const QString &errorString) const
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

void bridge::requestReport() const
{
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
    });
}

void bridge::updatePwd(const QString &newPwd) const
{
    const QJsonObject json{{"password", newPwd}};

    changePwd("changePassword", json);
}

void bridge::resetPwd(int id) const
{
    const QJsonObject json{{ "id", id }};

    changePwd("resetPassword", json);
}

void bridge::changePwd(const char *key, const QJsonObject &json) const
{
    mng->putToKey(key,
                  QJsonDocument(json).toJson(),
                  [this] (const QJsonObject& rep)
    { emit loaded(); },
    "changePwd error");
}

void bridge::lockUser(int id, const bool &locked) const
{
    const QJsonObject json{
        { "id", id },
        { "lock", locked }
    };

    mng->putToKey("lock",
                  QJsonDocument(json).toJson(),
                  [this] (const QJsonObject& rep)
    {
        emit loaded();
    },
    "loackUser error");
}

void bridge::getAccountDates() const
{
    std::string key{"accountState/"};
    key.append(std::to_string(accountId));

    mng->getFromKey(key.c_str(),
                    [this] (const QByteArray& rep)
    {
        const auto json{QJsonDocument::fromJson(rep).object()};
        if (json.contains("success"))
        {
            if (json["success"].toBool())
            {
                auto account{acnts->item_at_id(accountId)};
                account.read(json);
                acnts->setItemAtId(accountId, account);
                emit loaded();
                return;
            }
        }

        emit mng->replyError("getAccountDates error");
    });
}

void bridge::updateState(int newState) const
{
    const QJsonObject json{{ "id", accountId },
                           { "state", accountState + newState }};

    mng->putToKey("accountState",
                  QJsonDocument(json).toJson(),
                  [this] (const QJsonObject& rep)
    {
        auto account{acnts->item_at_id(accountId)};
        account.read(rep);
        acnts->setItemAtId(accountId, account);
        emit loaded();
    },
    "updateState error");
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

QUrl bridge::getPictureName(QString& name, int index) const
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

    bool uploaded{true};
    int flags{document_item::None};

    for (const auto& doc : docs->items())
    {
        if (!doc.isUploaded)
        {
            uploaded = false;
            break;
        }

        if (!hasFlag(flags, doc.category))
            flags += doc.category;
    }

    if (uploaded)
    {
        setDocumentsCompleted(flags == CATEGOIES_SUMED
                              || flags == (CATEGOIES_SUMED - document_item::Beb)
                              || flags == (CATEGOIES_SUMED - document_item::FutureJobs)
                              || flags == (CATEGOIES_SUMED - document_item::Beb
                                           - document_item::FutureJobs)
                              );
    }
    else
        setDocumentsCompleted(false);
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

    if (doc.isUploaded || doc.relativePath.isEmpty())
        return;

    QFile file{doc.relativePath.toLocalFile()};
    if (file.exists())
    {
        if (!file.open(QIODevice::ReadOnly))
            onException("upload_doc error", file.errorString());
        else
        {
            const auto bytes{file.readAll()};
            const auto body{QString(bytes.toBase64())};

            QJsonObject obj{};
            doc.write(obj);
            obj["body"] = body;

            QJsonDocument data{obj};
            int parent_account{accountId};

            mng->putToKey(docs->key(),
                          data.toJson(),
                          [this, parent_account, doc]
                          (const QJsonObject& rep)
            {
                auto updated_account{acnts->item_at_id(parent_account)};
                auto updated_doc{doc};

                Data::item_list<Data::document_item> updated_list{};
                updated_list.read(updated_account.get(&updated_list));

                if (rep.contains("document") && rep["document"].isObject())
                {
                    updated_doc.read(rep["document"].toObject());
                    updated_list.setItemAtId(updated_doc.id, updated_doc);
                }

                if (rep.contains("accountState") && rep["accountState"].isDouble())
                {
                    updated_account.state = Data::account_item::states(rep["accountState"].toInt());
                    updated_account.update(&updated_list);
                    acnts->setItemAtId(parent_account, updated_account);
                }

                qDebug() << "uploaded !";
                check_doc_completion();
            },
            "upload_doc error",
            [this](){});
        }
    }
    else
    { onException("upload_doc error", "Fichier introuvable"); }
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
    return (value & flag) == flag;
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
