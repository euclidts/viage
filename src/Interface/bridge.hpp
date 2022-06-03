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

    void downloadFile(const QString& key,
                      const QUrl &directory,
                      const QString &fileName) const;
    W_INVOKABLE(downloadFile, (const QString&,
                               const QUrl&,
                               const QString&))

    void requestReport(const QUrl& directory) const;
    W_INVOKABLE(requestReport, (const QUrl&))

    QUrl getPictureName(int id, QString& name, int index) const;
    W_INVOKABLE(getPictureName, (int, QString&, int))

    void setQmlObject(QObject* obj) noexcept { qmlObject = obj; }

    void setDocuments(Data::item_list<Data::document_item>* newDocuments);

    bool getDocumentsCompleted() const;
    void setDocumentsCompleted(bool newDocumentsCompleted);
    void documentsCompletedChanged()
    W_SIGNAL(documentsCompletedChanged)

    int getClearance() const;
    void clearanceChanged()
    W_SIGNAL(clearanceChanged)

    W_PROPERTY(bool, documentsCompleted READ getDocumentsCompleted NOTIFY documentsCompletedChanged)
    W_PROPERTY(int, clearance READ getClearance NOTIFY clearanceChanged)

    bool has_flag(int value, int flag) const noexcept;

private:
    QObject* qmlObject;
    netManager* mng;
    QTemporaryDir tempDir;
    QString rootPath;

    Data::item_list<Data::document_item>* docs;
    bool documentsCompleted{false};
    void check_doc_completion(int index);
    void uplaod_docs(int index);

    int &clearance{mng->user.clearance};

    Data::item_list<Data::account_item>* acnts;
    int accointId{0};

    const QString filePath(const QUrl& directory,
                           const QString& fileName) const;
};

}

#endif // BRIDGE_HPP
