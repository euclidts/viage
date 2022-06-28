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
               Data::item_list<Data::document_item>* documents)
    : mng{manager}
    , usrs{users}
    , acnts{accounts}
    , docs{documents}
    , tempDir{}
{
    if (tempDir.isValid())
        rootPath = tempDir.path();
    else
        qDebug() << "temp directory error :" << tempDir.errorString();

    connect(mng, &netManager::loggedIn,
            this, &bridge::onLogin);

    connect(mng, &netManager::userChanged,
            this, &bridge::setUserId);

    connect(mng, &netManager::clearanceChanged,
            this, &bridge::setClearance);

    using namespace Data;

    connect(acnts, &item_list<account_item>::postItemsAppended,
            this, &bridge::getLastAccount);

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
            this, &bridge::check_doc_completion);

    connect(docs, &item_list<document_item>::validate,
            this, &bridge::uplaod_docs);

    using namespace People;

    connect(usrs, &item_list<user_item>::postItemsAppended,
            this, &bridge::getLastUser);
}

void bridge::onLogin(const bool& success) const
{
    QMetaObject::invokeMethod(qmlObject,
                              "onLogin",
                              Q_ARG(bool, success));
}

void bridge::authenticate(const QString &username, const QString &password) const
{
    mng->authenticate(username, password);
}

void bridge::downloadFile(const QString &key, const QUrl &directory, const QString &fileName) const
{
    mng->downloadFile(key.toStdString().c_str(),
                      filePath(directory, fileName),
                      [] (bool success, const QString& string)
    {
        if (!success) qDebug() << "file error :" << string;
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
                qDebug() << "Desktop services : could not open excel";
        }
        else
            qDebug() << "file error :" << error;

        emit loaded();
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
                  [this] (const QByteArray& rep)
    {
        qDebug() << rep;
        emit loaded();
    });
}

void bridge::updateState(int newState) const
{
    const QJsonObject json{{ "id", accountId },
                           { "state", accountState + newState }};

    mng->putToKey("accountState",
                  QJsonDocument(json).toJson(),
                  [this] (const QByteArray& rep)
    {
        const auto json = QJsonDocument::fromJson(rep).object();
        if (json.contains("success") && json["success"].isBool())
        {
            if (json["success"].toBool())
            {
                auto account{acnts->item_at_id(accountId)};
                account.read(json);
                acnts->setItemAtId(accountId, account);
            }
            else
                qDebug() << "validate error :" << json["errorMessage"].toString();
        }

        emit loaded();
    });
}

QUrl bridge::getPictureName(QString& name, int index) const
{
    return QUrl::fromLocalFile(rootPath
                               + '/'
                               + QString::number(accountId)
                               + '_'
                               + name.replace(' ', '_')
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

    int flags{document_item::None};

    for (const auto& doc : docs->items())
    {
        if (!hasFlag(flags, doc.category))
            flags += doc.category;
    }

    setDocumentsCompleted(flags == CATEGOIES_SUMED
                          || flags == (CATEGOIES_SUMED - document_item::Beb)
                          || flags == (CATEGOIES_SUMED - document_item::FutureJobs)
                          || flags == (CATEGOIES_SUMED - document_item::Beb
                                       - document_item::FutureJobs)
                          );
}

void bridge::uplaod_docs(int index)
{
    for (const auto& doc : docs->items())
    {
        if (doc.category == Data::document_item::None)
        {
            // clean orphan documents
            QJsonObject obj{};
            obj["id"] = doc.id;

            QJsonDocument data{obj};

            mng->deleteToKey(docs->key(),
                             data.toJson(),
                             [](const QByteArray& rep)
            { qDebug() << "delete reply :" << rep; });
        }
        else if (!doc.isUploaded)
        {
            QFile file{doc.relativePath.path()};
            if (file.exists())
            {
                if (!file.open(QIODevice::ReadOnly))
                {
                    qDebug() << "couldn't open the file";
                    return;
                }

                const auto bytes{file.readAll()};
                const auto body{QString(bytes.toBase64())};

                QJsonObject obj{};
                doc.write(obj);
                obj["body"] = body;

                QJsonDocument data{obj};

                qDebug() << "uploading " << file.fileName();

                mng->putToKey(docs->key(),
                              data.toJson(),
                              [](const QByteArray& rep)
                { qDebug() << "upload reply :" << rep; });
            }
        }
    }
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
    qDebug() << "account recevied" << accountReceived;
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

void bridge::getLastAccount() noexcept
{
    if (onboarding)
    {
        onboarding = false;
        setAccoountId(acnts->items().constLast().id);
        setAccountState(0);
        emit requestOwners(accountId);
    }
}

void bridge::getLastUser() noexcept
{
    if (hiring)
    {
        hiring = false;
        setUserId(usrs->items().constLast().id);
        emit requestUser(userId);
    }
}

}
