#include <QVariant>

#include "senior_citizen_item.hpp"

namespace Data
{
namespace People
{
senior_citizen_item::senior_citizen_item()
{
}

QHash<int, QByteArray> senior_citizen_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[BirthDayRole] = "birthDay";
    names[SexRole] = "sex";

    return names;
}

QVariant senior_citizen_item::data(int role) const
{
    if (role == BirthDayRole)
        return QVariant(birthDay);
    else
        return QVariant(sex);

    return QVariant();
}

void senior_citizen_item::setData(const QVariant &value, int role)
{
    if (role == BirthDayRole)
    {
        const auto date{value.toDate()};
        birthDay.setDate(date.year(), date.month(), date.day());
    } else
        sex = sexes(value.toInt());
}

}

}
