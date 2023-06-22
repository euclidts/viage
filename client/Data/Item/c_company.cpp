#include "qjsonarray.h"
#include "qvariant.h"

#include "c_company.hpp"
#include <Item/team_item.hpp>
#include <c_list.hpp>
#include "c_team.hpp"
#include <client_utils.hpp>

using namespace client_utils;

namespace Data
{
c_company::c_company()
    : company_item{}
{
}

QHash<int, QByteArray> c_company::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[NameRole] = "name";
    names[TeamsRole] = "teams";

    return names;
}

QVariant c_company::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return QVariant(id);
    case NameRole:
        return to_QString(name);
    case TeamsRole:
        return to_QJsonArray(teams);
    }

    return QVariant();
}

void c_company::setData(const QVariant& value, int role)
{
    if (role == NameRole)
        name = to_string(value);
}


bool c_company::update(c_list<c_team>* ti)
{
    Json::Value arr{};
    ti->write(arr);
    if (teams == arr)
        return false;

    teams = arr;
    return true;
}

Json::Value c_company::get(c_list<c_team> *ti) const
{
    return teams;
}

}
