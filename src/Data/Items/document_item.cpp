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

    names[Category] = "category";
    names[IsUploaded] = "isUploaded";
    names[UrlRole] = "url";
    names[IdRole] = "id";

    return names;
}

QVariant document_item::data(int role) const
{
    switch (role)
    {
    case Category:
        return QVariant(category);
    case IsUploaded:
        return QVariant(isUploaded);
    case UrlRole:
        return QVariant(url);
    case IdRole:
        return QVariant(id);
    }

    return QVariant();
}

void document_item::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case Category:
        category = categories(value.toInt());
        break;
    case IsUploaded:
        isUploaded = value.toBool();
        break;
    case UrlRole:
        url = value.toUrl();
    case IdRole:
        id = value.toInt();
        break;
    }
}

void document_item::read(const QJsonObject& json)
{
    if (json.contains("category") && json["category"].isDouble())
        category = categories(json["category"].toInt());

    if (json.contains("isUploaded") && json["isUploaded"].isBool())
        isUploaded = json["isUploaded"].toBool();

    if (json.contains("url") && json["url"].isString())
        url = json["url"].toString();

    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();
}

void document_item::write(QJsonObject& json) const
{
    json["category"] = category;
    json["isUpoaded"] = isUploaded;
    json["url"] = url.toString();
    json["id"] = id;
}

bool document_item::is_completed() const
{
    if (url.isEmpty() || !isUploaded)
        return false;

    return true;
}

}
