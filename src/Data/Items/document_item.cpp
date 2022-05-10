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
    names[FileNameRole] = "fileName";
    names[ExtensionRole] = "extension";
    names[IsUploadedRole] = "isUploaded";
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
    case FileNameRole:
        return QVariant(fileName);
    case ExtensionRole:
        return QVariant(extension);
    case IsUploadedRole:
        return QVariant(isUploaded);
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
    case RelativePathRole:
    {
        relativePath = value.toUrl();
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

        if (json.contains("fileName") && json["fileName"].isString())
            fileName = json["fileName"].toString();

        if (json.contains("extension") && json["extension"].isString())
            extension = json["extension"].toString();
    }
    else
    {
        if (json.contains("relativePath") && json["relativePath"].isString())
            relativePath = json["relativePath"].toString();

        setFileInfo();
    }

    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();
}

void document_item::write(QJsonObject& json) const
{
    json["category"] = category;

    if (!isUploaded)
        json["relativePath"] = relativePath.toString();

    json["fileName"] = fileName;
    json["extension"] = extension;
    json["id"] = id;
}

bool document_item::is_completed() const
{
    if (fileName == "")
        return false;

    return true;
}

void document_item::setFileInfo()
{
    auto fullPath{relativePath.toLocalFile()};

    if (!relativePath.isLocalFile())
    {
        relativePath = "";
        extension = "";
        return;
    }

    auto withExtension{fullPath.split(QLatin1Char('/')).last()};
    auto splitedFile{withExtension.split(QLatin1Char('.'))};
    fileName = splitedFile[0];
    extension = splitedFile[1];
}

}
