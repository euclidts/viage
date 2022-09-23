#include <QVariant>

#include "document_item.hpp"

namespace Data
{
document_item::document_item()
{
}

QHash<int, QByteArray> document_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[CategoryRole] = "category";
    names[RelativePathRole] = "relativePath";
    names[LocalPathRole] = "localPath";
    names[FileNameRole] = "fileName";
    names[ExtensionRole] = "extension";
    names[IsUploadedRole] = "isUploaded";
    names[UploadingRole] = "uploading";
    names[UploadProgressRole] = "uploadProgress";
    names[UploadDateRole] = "uploadDate";
    names[IdRole] = "id";

    return names;
}

QVariant document_item::data(int role) const
{
    switch (role)
    {
    case CategoryRole:
        return QVariant(category);
    case RelativePathRole:
        return QVariant(relativePath);
    case LocalPathRole:
        return QVariant(localPath);
    case FileNameRole:
        return QVariant(fileName);
    case ExtensionRole:
        return QVariant(extension);
    case IsUploadedRole:
        return QVariant(isUploaded);
    case UploadingRole:
        return QVariant(uploading);
    case UploadProgressRole:
        return QVariant(uploadProgress);
    case UploadDateRole:
        return QVariant(uploadDate);
    case IdRole:
        return QVariant(id);
    }

    return QVariant();
}

void document_item::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case CategoryRole:
        category = categories(value.toInt());
        break;
    case LocalPathRole:
    {
        localPath = value.toUrl();
        setFileInfo();
        isUploaded = false;
        break;
    }
    }
}

void document_item::read(const QJsonObject& json)
{
    if (json.contains("category") && json["category"].isDouble())
        category = categories(json["category"].toInt());

    if (json.contains("isUploaded") && json["isUploaded"].isBool())
        isUploaded = json["isUploaded"].toBool();

    if(isUploaded)
    {
        if (json.contains("uploadDate") && json["uplaodDate"].isString())
            uploadDate = QDate::fromString(json["uploadDate"].toString(), "jj.MM.yyyy");
    }

    if (json.contains("localPath") && json["localPath"].isString())
        QUrl url{json["relativePath"].toString()};

    if (json.contains("relativePath") && json["relativePath"].isString())
        relativePath = json["relativePath"].toString();

    setFileInfo();

    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();
}

void document_item::write(QJsonObject& json) const
{
    json["category"] = category;
    json["isUploaded"] = isUploaded;
    json["fileName"] = fileName;
    json["extension"] = extension;
    json["id"] = id;
}

bool document_item::is_completed() const
{
    if (fileName == "")
        return false;

    return isUploaded;
}

void document_item::setFileInfo()
{
    if (localPath.isEmpty() && relativePath.isEmpty())
        return;

    QString fullPath{};

    if (!localPath.isEmpty())
        fullPath = localPath.toLocalFile();
    else
        fullPath = relativePath.toLocalFile();

    auto withExtension{fullPath.split(QLatin1Char('/')).back()};
    auto splitedFile{withExtension.split(QLatin1Char('.'))};

    extension = splitedFile.back();
    splitedFile.pop_back();
    fileName = splitedFile.join(QLatin1Char('.'));
}

}
