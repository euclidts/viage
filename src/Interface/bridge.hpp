#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <QObject>
#include <QStandardPaths>
#include <QTemporaryDir>

#include <wobjectdefs.h>

#include "netManager.hpp"

namespace Data
{
struct document_item;
struct account_item;

template <typename T>
class item_list;
}

namespace Interface
{
class bridge final : public QObject
{
    W_OBJECT(bridge)

public:
    bridge(Interface::netManager* manager,
           Data::item_list<Data::account_item>* accounts,
           Data::item_list<Data::document_item>* documents);

    void onLogin(const bool& success) const;

    void authenticate(const QString& username, const QString& password) const;
    W_INVOKABLE(authenticate, (const QString&, const QString&))

    void onboard();
    W_INVOKABLE(onboard)

    void downloadFile(const QString& key,
                      const QUrl &directory,
                      const QString &fileName) const;
    W_INVOKABLE(downloadFile, (const QString&,
                               const QUrl&,
                               const QString&))

    void requestReport() const;
    W_INVOKABLE(requestReport)

    QUrl getPictureName(int id, QString& name, int index) const;
    W_INVOKABLE(getPictureName, (int, QString&, int))

    void setQmlObject(QObject* obj) noexcept { qmlObject = obj; }

    bool has_flag(int value, int flag) const noexcept;
    bool accountHasFlag(int flag) const noexcept;
    W_INVOKABLE(accountHasFlag, (int))

    void loaded() const
    W_SIGNAL(loaded)

    void requestOwners(int id)
    W_SIGNAL(requestOwners, id)

    int getAccountId() const;
    void setAccountId(int newAccountId);
    void accountIdChanged()
    W_SIGNAL(accountIdChanged)

    int getAccountState() const;
    void setAccountState(int newAccountState);
    void accountStateChanged()
    W_SIGNAL(accountStateChanged)

    bool getDocumentsCompleted() const;
    void setDocumentsCompleted(bool newDocumentsCompleted);
    void documentsCompletedChanged()
    W_SIGNAL(documentsCompletedChanged)

    int getClearance() const;
    void clearanceChanged()
    W_SIGNAL(clearanceChanged)

    W_PROPERTY(bool, documentsCompleted READ getDocumentsCompleted NOTIFY documentsCompletedChanged)
    W_PROPERTY(int, clearance READ getClearance NOTIFY clearanceChanged)
    W_PROPERTY(int, accountId READ getAccountId WRITE setAccountId NOTIFY accountIdChanged)
    W_PROPERTY(int, accountState READ getAccountState WRITE setAccountState NOTIFY accountStateChanged)

private:
    QObject* qmlObject;
    netManager* mng;
    QTemporaryDir tempDir;
    QString rootPath;

    bool onboarding{false};

    Data::item_list<Data::document_item>* docs;
    bool documentsCompleted{false};
    void check_doc_completion(int index);
    void uplaod_docs(int index);

    int &clearance{mng->user.clearance};

    Data::item_list<Data::account_item>* acnts;
    int accountId{0};
    int accountState{0};

    const QString filePath(const QUrl& directory,
                           const QString& fileName) const;

    void getLastAccount() noexcept;
};

}

#endif // BRIDGE_HPP
