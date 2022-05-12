#include <QDate>
#include <QUrl>
#include <QFile>

#include <wobjectimpl.h>

#include "bridge.hpp"
#include "netManager.hpp"
#include <Items/document_item.hpp>
#include <Lists/item_list.hpp>

namespace Interface
{
W_OBJECT_IMPL(bridge)

bridge::bridge(Interface::netManager* manager, Data::item_list<Data::document_item> *documents)
    : mng{manager}
    , docs{documents}

{
    connect(mng, &netManager::loggedIn,
            this, &bridge::onLogin);

    using namespace Data;

    connect(docs, &item_list<document_item>::dataChangedAt,
            this, &bridge::check_doc_completion);

// curently does not work
//    connect(docs, &item_list<document_item>::validate,
//            this, &bridge::uplaod_docs);
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
    mng->downloadFile(key.toStdString().c_str(), filePath(directory, fileName));
}

void bridge::requestReport(const QUrl &directory) const
{
    auto now{QDateTime::currentDateTime()};

    QString fileName{"Viage-"};
    fileName.append(now.toString("dd-MM-yy-hh-mm"));
    fileName.append(".xlsb");

    mng->downloadFile("export/accounts", filePath(directory, fileName));
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

void bridge::check_doc_completion(int index)
{
    using namespace Data;

    int flags{document_item::None};

    for (const auto& doc : docs->items())
    {
        if (!has_flag(flags, doc.category))
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
        if (!doc.isUploaded)
        {
            QFile file{doc.relativePath.path()};
            if (file.exists())
            {
                if (!file.open(QIODevice::ReadOnly))
                {
                    qDebug() << "couldn't open the file";
                    return;
                }

                const auto size{file.size()};
                char bytes[size];

                QJsonObject obj{ { "id", doc.id},
                                 { "body", bytes }
                               };

                QJsonDocument data{obj};

                mng->putToKey(docs->key(),
                              data.toJson(),
                              [](const QByteArray& rep)
                { qDebug() << "upload reply :" << rep; });
            }
        }
    }
}

bool bridge::has_flag(int value, int flag) const noexcept
{
    return (value & flag) == flag;
}

void bridge::setDocuments(Data::item_list<Data::document_item>* newDocuments)
{
    docs = newDocuments;
}

const QString bridge::filePath(const QUrl &directory, const QString &fileName) const
{
    auto filePath{directory.path()};
    filePath.append('/');
    filePath.append(fileName);

    const auto fullPath{QUrl::fromLocalFile(fileName)};

    return fullPath.toLocalFile();
}
}
