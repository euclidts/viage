#include <QVariant>

#include "c_address.hpp"
#include <Item/address_item.hpp>

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
        return QVariant(QString::fromStdString(address->street));
    case ZipRole:
        return QVariant(address->zip);
    case CantonRole:
        return QVariant(QString::fromStdString(address->canton));
    case CityRole:
        return QVariant(QString::fromStdString(address->city));
    }

    return QVariant();
}

void c_address::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case StreetRole:
        address->street = value.toString().toStdString();
        break;
    case ZipRole:
        address->zip = value.toInt();
        break;
    case CantonRole:
        address->canton = value.toString().toStdString();
        break;
    case CityRole:
        address->city = value.toString().toStdString();
        break;
    }
}

}
}
