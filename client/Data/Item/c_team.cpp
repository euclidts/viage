#include "qvariant.h"

#include "c_team.hpp"
#include <client_utils.hpp>

using namespace Utils;

namespace Data
{

c_team::c_team()
    : team_item{}
{
}

QHash<int, QByteArray> Data::c_team::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[CaptionRole] = "caption";
    names[HasUsersRole] = "hasUsers";

    return names;
}

QVariant c_team::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return QVariant(id);
    case CaptionRole:
        return to_QString(caption);
    case HasUsersRole:
        return QVariant(has_users);
    }

    return QVariant();
}

void c_team::setData(const QVariant& value, int role)
{
    if (role == CaptionRole)
        caption = to_string(value.toString());

    if (role == HasUsersRole)
        has_users = value.toBool();
}

}
