#include <QVariant>
#include <QJsonArray>

#include "team.hpp"

namespace Data
{
team::team()
    : base_item<team>{}
{}

QHash<int, QByteArray> Data::team::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[CaptionRole] = "caption";
    names[HasUsersRole] = "hasUsers";

    return names;
}

QVariant team::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return id;
    case CaptionRole:
        return caption;
    case HasUsersRole:
        return has_users;
    }

    return QVariant{};
}

void team::setData(const QVariant& value, int role)
{
    if (role == CaptionRole)
        caption = value.toString();

    if (role == HasUsersRole)
        has_users = value.toBool();
}

void team::read(const QJsonObject& json)
{
    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();

    if (json.contains("caption") && json["caption"].isString())
        caption = json["caption"].toString();

    if (json.contains("users") && json["users"].isArray())
        has_users = !json["users"].toArray().isEmpty();
}

void team::write(QJsonObject& json) const
{
    json["id"] = id;
    json["caption"] = caption;
}

bool team::is_completed() const
{
    if (caption == "")
        return false;

    return true;
}
}
