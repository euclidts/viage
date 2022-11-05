#include <QJsonObject>
#include "team_item.hpp"

namespace Data
{

team_item::team_item()
{
}

QHash<int, QByteArray> Data::team_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[CaptionRole] = "caption";
    names[HasUsersRole] = "hasUsers";

    return names;
}

QVariant team_item::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return QVariant(id);
    case CaptionRole:
        return QVariant(caption);
    case HasUsersRole:
        return QVariant(has_users);
    }

    return QVariant();
}

void team_item::setData(const QVariant& value, int role)
{
    if (role == CaptionRole)
        caption = value.toString();

    if (role == HasUsersRole)
        has_users = value.toBool();
}

void team_item::read(const QJsonObject& json)
{
    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();

    if (json.contains("caption") && json["caption"].isString())
        caption = json["caption"].toString();

    if (json.contains("users") && json["users"].isArray())
        has_users = !json["users"].toArray().isEmpty();
}

void team_item::write(QJsonObject& json) const
{
    json["id"] = id;
    json["caption"] = caption;
}

bool team_item::is_completed() const
{
    if (caption == "")
        return false;

    return true;
}

}
