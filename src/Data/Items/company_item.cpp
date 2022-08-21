#include <QJsonObject>

#include "company_item.hpp"
#include "team_item.hpp"

#include <Lists/item_list.hpp>

namespace Data
{

company_item::company_item()
{
}

QHash<int, QByteArray> Data::company_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[NameRole] = "name";
    names[TeamsRole] = "teams";

    return names;
}

QVariant company_item::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return QVariant(id);
    case NameRole:
        return QVariant(name);
    case TeamsRole:
        return teams.toVariantList();
    }

    return QVariant();
}

void company_item::setData(const QVariant& value, int role)
{
    if (role == NameRole)
        name = value.toString();
    else if(role == TeamsRole)
        teams = value.toJsonArray();
}

void company_item::set(item_list<team_item>* ti)
{
    QJsonArray arr{};
    ti->write(arr);

}

void company_item::read(const QJsonObject& json)
{
    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();

    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    if (json.contains("teams") && json["teams"].isArray())
        teams = json["teams"].toArray();
}

void company_item::write(QJsonObject& json) const
{
    json["id"] = id;
    json["name"] = name;
    json["teams"] = teams;
}

bool company_item::is_completed() const
{
    if (name == "")
        return false;

    return true;
}

}
