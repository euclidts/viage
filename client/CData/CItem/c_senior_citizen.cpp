#include <QVariant>
#include <QDate>

#include "c_senior_citizen.hpp"

namespace Data
{
namespace People
{
c_senior_citizen::c_senior_citizen()
{
    const auto minAge{QDate::currentDate().addYears(-AGE_MIN)};
    this->birthDay = minAge.toString("dd.MM.yyyy").toStdString();
}

QHash<int, QByteArray> c_senior_citizen::roleNames()
{
    QHash<int, QByteArray> names;

    names[BirthDayRole] = "birthDay";
    names[SexRole] = "sex";

    return names;
}

QVariant c_senior_citizen::data(int role) const
{
    if (role == BirthDayRole)
    {
        const auto value{QString::fromStdString(birthDay)};
        return QDate::fromString(value, "dd.MM.yyyy");
    }
    else
        return QVariant(sex);

    return QVariant();
}

void c_senior_citizen::setData(const QVariant &value, int role)
{
    if (role == BirthDayRole)
    {
        const auto date{value.toDate()};
        birthDay = date.toString("dd.MM.yyyy").toStdString();
    } else
        sex = sexes(value.toInt());
}

}

}
