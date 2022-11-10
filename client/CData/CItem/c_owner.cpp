#include <QJsonObject>
#include <QJsonArray>

#include "c_owner.hpp"

#include <Item/senior_citizen_item.hpp> // for age Macros

namespace Data
{
namespace People {

c_owner::c_owner()
    : owner_item{}
    , c_infant{}
    , ca{&address}
{
    const auto yearsAgo{QDate::currentDate().addYears(-AGE_MIN)};

    this->birthDay = yearsAgo.toString().toStdString();
}

QHash<int, QByteArray> c_owner::roleNames()
{
    QHash<int, QByteArray> names = c_infant::roleNames();

    names[BirthDayRole] = "birthDay";
    names[CivilStatusRole] = "civilStatus";
    names[AVSRole] = "avs";

    names.insert(Places::c_address::roleNames());

    return names;
}

QVariant c_owner::data(int role) const
{
    QVariant extra_data{c_infant::data(role)};

    if (extra_data != QVariant())
        return extra_data;

    switch (role)
    {
    case BirthDayRole:
    {
        const auto date{QString::fromStdString(birthDay)};
        return QDate::fromString(date, "yyyy-MM-dd");
    }
    case CivilStatusRole:
        return QVariant(civilStatus);
    case AVSRole:
        return QString::fromStdString(avs);
    }

    extra_data = ca.data(role);

    if (extra_data != QVariant())
        return extra_data;

    return QVariant();
}

void c_owner::setData(const QVariant &value, int role)
{
    c_infant::setData(value, role);

    switch (role)
    {
    case BirthDayRole:
    {
        const auto date{value.toDate()};
        birthDay = date.toString("dd.MM.yyyy").toStdString();
        break;
    }
    case CivilStatusRole:
        civilStatus = civilStates(value.toInt());
        break;
    case AVSRole:
        avs = value.toString().toStdString();
        break;
    }

    ca.setData(value, role);
}

}
}
