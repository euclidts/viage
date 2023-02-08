#include <QVariant>
#include "qurl.h"

#include "c_document.hpp"
#include <utils.hpp>

using namespace Utils;

namespace Data
{
c_document::c_document()
    : document_item{}
{
}

QHash<int, QByteArray> c_document::roleNames()
{
    QHash<int, QByteArray> names;

    names[CategoryRole] = "category";
    names[LocalPathRole] = "localPath";
    names[FileNameRole] = "fileName";
    names[ExtensionRole] = "extension";
    names[StateRole] = "state";
    names[UploadProgressRole] = "uploadProgress";
    names[UploadDateRole] = "uploadDate";
    names[IdRole] = "id";

    return names;
}

QVariant c_document::data(int role) const
{
    switch (role)
    {
    case CategoryRole:
        return QVariant(category);
    case LocalPathRole:
        return to_QString(localPath.string());
    case FileNameRole:
        return to_QString(fileName);
    case ExtensionRole:
        return to_QString(extension);
    case StateRole:
        return QVariant(state);
    case UploadProgressRole:
        return QVariant(uploadProgress);
    case UploadDateRole:
        return to_QDate(uploadDate);
    case IdRole:
        return QVariant(id);
    }

    return QVariant();
}

void c_document::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case CategoryRole:
        category = categories(value.toInt());
        break;
    case LocalPathRole:
    {
        localPath = value.toUrl().toLocalFile().toStdString();
        set_file_info();
        state = NotUploded;
        break;
    }
    }
}

}
