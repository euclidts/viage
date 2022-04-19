#include <QVariant>

#include "url_item.hpp"

namespace Data
{
url_item::url_item()
{
}

url_item::url_item(const QJsonObject &json)
{
    read(json);
}

QHash<int, QByteArray> url_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[UrlRole] = "url";
    names[IdRole] = "id";

    return names;
}

QVariant url_item::data(int role) const
{
    if (role == UrlRole)
        return QVariant(url);
    else if (role == IdRole)
        return QVariant(id);

    return QVariant();
}

void url_item::setData(const QVariant &value, int role)
{
    if (role == UrlRole)
        url = value.toUrl();
    else if (role == IdRole)
        id = value.toInt();
}

void url_item::read(const QJsonObject& json)
{
    if (json.contains("url") && json["url"].isString())
        url = json["url"].toString();

    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();
}

void url_item::write(QJsonObject& json) const
{
    json["url"] = url.toString();
    json["id"] = id;
}

}
