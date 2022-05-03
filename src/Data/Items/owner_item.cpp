//#include <chrono>

#include <QJsonObject>
#include <QJsonArray>

#include "owner_item.hpp"

namespace Data
{
namespace People {

owner_item::owner_item()
    : infant_item()
    , address_item()
    , birthDay{QDate::currentDate().addYears(-minAge)}
{
    //    using namespace std::chrono;

    //    auto tp = system_clock::now();
    //    auto dp = floor<days>(tp);
    //    year_month_day ymd{dp};
    //    birthYear = (int)ymd.year() - 100;
}

QHash<int, QByteArray> owner_item::roleNames()
{
    QHash<int, QByteArray> names = infant_item::roleNames();

    names[BirthDayRole] = "birthDay";
    names[CivilStatusRole] = "civilStatus";
    names[AVSRole] = "avs";

    names.insert(address_item::roleNames());

    return names;
}

QVariant owner_item::data(int role) const
{
    QVariant extra_data{infant_item::data(role)};

    if (extra_data != QVariant())
        return extra_data;

    switch (role)
    {
    case BirthDayRole:
        return QVariant(birthDay);
    case CivilStatusRole:
        return QVariant(civilStatus);
    case AVSRole:
        return QVariant(avs);
    }

    extra_data = address_item::data(role);

    if (extra_data != QVariant())
        return extra_data;

    return QVariant();
}

void owner_item::setData(const QVariant &value, int role)
{
    infant_item::setData(value, role);

    switch (role)
    {
    case BirthDayRole:
    {
        const auto date{value.toDate()};
        birthDay.setDate(date.year(), date.month(), date.day());
    }
        break;
    case CivilStatusRole:
        civilStatus = civilStates(value.toInt());
        break;
    case AVSRole:
        avs = value.toString();
        break;
    }

    address_item::setData(value, role);
}

void owner_item::read(const QJsonObject &json)
{
    infant_item::read(json);

    if (json.contains("birthDay") && json["birthDay"].isString())
        birthDay = QDate::fromString(json["birthDay"].toString(), "dd.MM.yyyy");

    if (json.contains("civilStatus") && json["civilStatus"].isDouble())
        civilStatus = civilStates(json["civilStatus"].toInt());

    if (json.contains("avs") && json["avs"].isString())
        avs = json["avs"].toString();

    if (json.contains("address") && json["address"].isObject())
        address_item::read(json["address"].toObject());
}

void owner_item::write(QJsonObject& json) const
{
    infant_item::write(json);

    json["birthDay"] = birthDay.toString("dd.MM.yyyy");
    json["civilStatus"] = civilStatus;
    json["avs"] = avs;

    QJsonObject jsonAddress{};
    address_item::write(jsonAddress);

    json["address"] = jsonAddress;
}

}
}
