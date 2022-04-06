#include <QVariant>

#include "address_item.hpp"

namespace Data
{
namespace Places
{
address_item::address_item()
{
}

QHash<int, QByteArray> address_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[StreetRole] = "street";
    names[ZipRole] = "zip";
    names[CantonRole] = "canton";
    names[CityRole] = "city";

    return names;
}

QVariant address_item::data(int role) const
{
    switch (role)
    {
    case StreetRole:
        return QVariant(street);
    case ZipRole:
        return QVariant(zip);
    case CantonRole:
        return QVariant(canton);
    case CityRole:
        return QVariant(city);
    }

    return QVariant();
}

void address_item::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case StreetRole:
        street = value.toString();
        break;
    case ZipRole:
        zip = value.toInt();
        break;
    case CantonRole:
        canton = value.toString();
        break;
    case CityRole:
        city = value.toString();
    }
}

void address_item::read(const QJsonObject& json)
{
    if (json.contains("street") && json["street"].isString())
        street = json["street"].toString();

    if (json.contains("zip") && json["zip"].isDouble())
        zip = json["zip"].toInt();

    if (json.contains("canton") && json["canton"].isString())
        canton = json["canton"].toString();

    if (json.contains("city") && json["city"].isString())
        city = json["city"].toString();
}

void address_item::write(QJsonObject& json) const
{
    json["street"] = street;
    json["zip"] = zip;
    json["canton"] = canton;
    json["city"] = city;
}

}
}
