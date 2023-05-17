#include <QJsonObject>
#include <QJsonArray>

#include "c_owner.hpp"
#include <Item/senior_citizen_item.hpp> // for age Macros
#include <client_utils.hpp>

using namespace Utils;

namespace Data
{
namespace People {

c_owner::c_owner()
    : owner_item{}
    , c_infant{}
    , ca{address}
{
    birthDay = to_date(QDate::currentDate().addYears(-AGE_MIN));
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
        return to_QDate(birthDay);
    case CivilStatusRole:
        return QVariant(civilStatus);
    case AVSRole:
        return to_QString(avs);
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
        birthDay = to_date(value.toDate());
        break;
    case CivilStatusRole:
        civilStatus = civilStates(value.toInt());
        break;
    case AVSRole:
        avs = to_string(value.toString());
        break;
    }

    ca.setData(value, role);
}

}
}
