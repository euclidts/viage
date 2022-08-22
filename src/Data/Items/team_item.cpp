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
    names[NameRole] = "name";
    names[HasUsersRole] = "hasUsers";

    return names;
}

QVariant team_item::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return QVariant(id);
    case NameRole:
        return QVariant(name);
    case HasUsersRole:
        return QVariant(has_users);
    }

    return QVariant();
}

void team_item::setData(const QVariant& value, int role)
{
    if (role == NameRole)
        name = value.toString();

    if (role == HasUsersRole)
        has_users = value.toBool();
}

void team_item::read(const QJsonObject& json)
{
    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();

    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    if (json.contains("hasUsers") && json["hasUsers"].isBool())
        has_users = json["hasUsers"].toBool();
}

void team_item::write(QJsonObject& json) const
{
    json["id"] = id;
    json["name"] = name;
}

bool team_item::is_completed() const
{
    if (name == "")
        return false;

    return true;
}

}
