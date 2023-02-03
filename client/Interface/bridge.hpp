#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <QObject>
#include <QStandardPaths>
#include <QTemporaryDir>

#include <wobjectdefs.h>

#include "netManager.hpp"
#include <Item/c_user.hpp>
#include <Item/c_document.hpp>

namespace Data
{
struct c_account;

template <typename T>
class c_list;
}

namespace Interface
{
class bridge final : public QObject
{
    W_OBJECT(bridge)

public:
    bridge(Interface::netManager* manager,
           Data::c_list<Data::People::c_user>* users,
           Data::c_list<Data::c_account>* accounts,
           Data::c_list<Data::c_document>* documents,
           const QString& path);

    void onLogin(const bool& success, const QString& errorString) const;

    void onException(const QString& prefix,
                     const QString& errorString) const;

    void authenticate(const QString& username, const QString& password) const;
    W_INVOKABLE(authenticate, (const QString&, const QString&))

    void onboard();
    W_INVOKABLE(onboard)
    void hire();
    W_INVOKABLE(hire)

    void downloadFile(const QString& key,
                      const QUrl &directory,
                      const QString &fileName) const;
    W_INVOKABLE(downloadFile, (const QString&,
                               const QUrl&,
                               const QString&))

    void requestReport();
    W_INVOKABLE(requestReport)

    void requestAccount();
    W_INVOKABLE(requestAccount)

    void requestEmail();
    W_INVOKABLE(requestEmail)

    void updatePwd(const QString& newPwd) const;
    W_INVOKABLE(updatePwd)

    void lockUser(int id, const bool& locked) const;
    W_INVOKABLE(lockUser)

    void getAccountDates() const;
    W_INVOKABLE(getAccountDates)

    void updateState(int newState) const;
    W_INVOKABLE(updateState)

    void sendOnboardedEmail() const;
    W_INVOKABLE(sendOnboardedEmail)

    void resetPwd(int id) const;
    W_INVOKABLE(resetPwd)

    QUrl getPictureName(QString name, int index) const;
    W_INVOKABLE(getPictureName, (QString, int))

    void setQmlObject(QObject* obj) noexcept { qmlObject = obj; }

    bool hasFlag(int value, int flag) const noexcept;
    W_INVOKABLE(hasFlag, (int, int))
    bool accountHasFlag(int flag) const noexcept;
    W_INVOKABLE(accountHasFlag, (int))

    void loaded() const
    W_SIGNAL(loaded)

    void requestUser(int id)
    W_SIGNAL(requestUser, id)

    void requestOwners(int id)
    W_SIGNAL(requestOwners, id)

    int getAccountId() const;
    void setAccoountId(int newAccountId);
    void accountIdChanged()
    W_SIGNAL(accountIdChanged)

    int getAccountState() const;
    void setAccountState(int newAccountState);
    void accountStateChanged()
    W_SIGNAL(accountStateChanged)

    bool getPPE() const;
    void setPPE(bool newPPE);
    void ppeChanged()
    W_SIGNAL(ppeChanged)

    bool getDocumentsCompleted() const;
    void setDocumentsCompleted(bool newDocumentsCompleted);
    void documentsCompletedChanged()
    W_SIGNAL(documentsCompletedChanged)

    Data::People::user_item::clearances getClearance() const;
    void setClearance(int newClearance);
    void clearanceChanged()
    W_SIGNAL(clearanceChanged)

    int getUserId() const;
    void setUserId(int newUserId);
    void userIdChanged()
    W_SIGNAL(userIdChanged)

    const QDate &getAccountReceived() const;
    void setAccountReceived(const QDate &newAccountReceived);
    void accountReceivedChanged()
    W_SIGNAL(accountReceivedChanged)

    const QDate &getAccountTransmited() const;
    void setAccountTransmited(const QDate &newAccountTransmited);
    void accountTransmitedChanged()
    W_SIGNAL(accountTransmitedChanged)

    const QDate &getAccountExpertized() const;
    void setAccountExpertized(const QDate &newAccountExpertized);
    void accountExpertizedChanged()
    W_SIGNAL(accountExpertizedChanged)

    const QDate &getAccountNotarized() const;
    void setAccountNotarized(const QDate &newAccountNotarized);
    void accountNotarizedChanged()
    W_SIGNAL(accountNotarizedChanged)

    const QDate &getAccountPaid() const;
    void setAccountPaid(const QDate &newAccountPaid);
    void accountPaidChanged()
    W_SIGNAL(accountPaidChanged)

    const QDate &getAccountDecided() const;
    void setAccountDecided(const QDate &newAccountDecided);
    void accountDecidedChanged()
    W_SIGNAL(accountDecidedChanged)

    float getDownloadProgress() const;
    void setDownloadProgress(float newDownloadProgress);
    void downloadProgressChanged()
    W_SIGNAL(downloadProgressChanged);

    W_PROPERTY(bool, documentsCompleted READ getDocumentsCompleted NOTIFY documentsCompletedChanged)
    W_PROPERTY(Data::People::user_item::clearances, clearance READ getClearance NOTIFY clearanceChanged)
    W_PROPERTY(int, userId READ getUserId NOTIFY userIdChanged)
    W_PROPERTY(int, accountId READ getAccountId WRITE setAccoountId NOTIFY accountIdChanged)
    W_PROPERTY(bool, ppe READ getPPE WRITE setPPE NOTIFY ppeChanged)
    W_PROPERTY(int, accountState READ getAccountState WRITE setAccountState NOTIFY accountStateChanged)
    W_PROPERTY(QDate, accountReceived READ getAccountReceived NOTIFY accountReceivedChanged)
    W_PROPERTY(QDate, accountTransmited READ getAccountTransmited NOTIFY accountTransmitedChanged)
    W_PROPERTY(QDate, accountExpertized READ getAccountExpertized NOTIFY accountExpertizedChanged)
    W_PROPERTY(QDate, accountNotarized READ getAccountNotarized NOTIFY accountNotarizedChanged)
    W_PROPERTY(QDate, accountPaid READ getAccountPaid NOTIFY accountPaidChanged)
    W_PROPERTY(QDate, accountDecided READ getAccountDecided NOTIFY accountDecidedChanged)
    W_PROPERTY(float, downloadProgress READ getDownloadProgress WRITE setDownloadProgress NOTIFY downloadProgressChanged)

private:
    QObject* qmlObject;
    netManager* mng;
    QString rootPath;

    bool onboarding{false};
    bool hiring{false};

    Data::c_list<Data::c_document>* docs;
    bool documentsCompleted{false};
    void check_doc_completion();
    void cleanup_docs(int ai);
    void upload_doc(int index);

    int userId{0};
    Data::People::user_item::clearances clearance{Data::People::user_item::None};

    Data::c_list<Data::People::c_user>* usrs;
    Data::c_list<Data::c_account>* acnts;
    int accountId{0};
    int accountState{0};
    bool ppe{false};
    QDate accountReceived{};
    QDate accountTransmited{};
    QDate accountExpertized{};
    QDate accountDecided{};
    QDate accountNotarized{};
    QDate accountPaid{};
    float downloadProgress{-1.f};

    const QString filePath(const QUrl& directory,
                           const QString& fileName) const;

    void changePwd(const char* key, const Json::Value& json) const;
};

}

#endif // BRIDGE_HPP
