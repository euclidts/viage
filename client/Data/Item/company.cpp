#include <QJsonArray>
#include <QVariant>

#include "company.hpp"
#include <list.hpp>
#include "team.hpp"

namespace Data
{
company::company()
    : base_item<company>{}
{}

QHash<int, QByteArray> company::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[NameRole] = "name";
    names[TeamsRole] = "teams";

    return names;
}

QVariant company::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return id;
    case NameRole:
        return name;
    case TeamsRole:
        return teams;
    }

    return QVariant{};
}

void company::setData(const QVariant& value, int role)
{
    if (role == NameRole)
        name = value.toString();
}


bool company::update(list<team>* ti)
{
    QJsonArray arr{};
    ti->write(arr);
    if (teams == arr)
        return false;

    teams = arr;
    return true;
}

QJsonArray company::get(list<team>* ti) const
{
    return teams;
}

void company::read(const QJsonObject& json)
{
    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();

    if (json.contains("name") && json["name"].isString())
        name = json["name"].toString();

    if (json.contains("teams") && json["teams"].isArray())
        teams = json["teams"].toArray();
}

void company::write(QJsonObject& json) const
{
    json["id"] = id;
    json["name"] = name;
    json["teams"] = teams;
}

bool company::is_completed() const
{
    if (name.isEmpty())
        return false;

    return true;
}

}
