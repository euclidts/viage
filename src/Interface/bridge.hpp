#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <QObject>

#include <wobjectdefs.h>

namespace Data
{
struct document_item;

template <typename T>
class item_list;
}

namespace Interface
{
class netManager;

class bridge final : public QObject
{
    W_OBJECT(bridge)

public:
    bridge(Interface::netManager* manager,
           Data::item_list<Data::document_item>* docs);

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

    void setQmlObject(QObject* obj) noexcept { qmlObject = obj; }

    void setDocuments(Data::item_list<Data::document_item>* newDocuments);

    bool getDocumentsCompleted() const;
    void setDocumentsCompleted(bool newDocumentsCompleted);
    void documentsCompletedChanged()
    W_SIGNAL(documentsCompletedChanged)

    W_PROPERTY(bool, documentsCompleted READ getDocumentsCompleted NOTIFY documentsCompletedChanged)

private:
    QObject* qmlObject;
    netManager* mng;

    Data::item_list<Data::document_item>* docs;
    bool documentsCompleted;
    void check_doc_completion(int index);
    void uplaod_docs(int index);

    bool has_flag(int value, int flag) const noexcept;

    const QString filePath(const QUrl& directory,
                           const QString& fileName) const;
};

}

#endif // BRIDGE_HPP
