#include "c_company.hpp"
#include "qjsonarray.h"
#include "qvariant.h"
#include <Item/team_item.hpp>

#include <List/item_list.hpp>

namespace Data
{
c_company::c_company()
    : c_base_item{}
    , company_item{}
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

}
