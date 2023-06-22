#include <QVariant>

#include "c_address.hpp"
#include <Item/address_item.hpp>
#include <iostream>
#include "client_utils.hpp"

using namespace client_utils;

namespace Data
{
namespace Places
{
c_address::c_address(address_item* ai)
    : address{ai}
{
}

QHash<int, QByteArray> c_address::roleNames()
{
    QHash<int, QByteArray> names;

    names[StreetRole] = "street";
    names[ZipRole] = "zip";
    names[CantonRole] = "canton";
    names[CityRole] = "city";

    return names;
}

QVariant c_address::data(int role) const
{
    switch (role)
    {
    case StreetRole:
        return to_QString(address->street);
    case ZipRole:
        return QVariant(address->zip);
    case CantonRole:
        return to_QString(address->canton);
    case CityRole:
        return to_QString(address->city);
    }

    return QVariant();
}

void c_address::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case StreetRole:
        address->street = to_string(value);
        break;
    case ZipRole:
        address->zip = value.toInt();
        break;
    case CantonRole:
        address->canton = to_string(value);
        break;
    case CityRole:
        address->city = to_string(value);
        break;
    }
}

}
}
