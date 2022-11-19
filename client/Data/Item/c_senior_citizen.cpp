#include <QVariant>
#include <QDate>

#include "c_senior_citizen.hpp"

namespace Data
{
namespace People
{
c_senior_citizen::c_senior_citizen()
    : senior_citizen_item{}
    , c_base_item{}
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
        return to_QDate(birthDay, "dd.MM.yyyy");
    else
        return QVariant(sex);

    return QVariant();
}

void c_senior_citizen::setData(const QVariant &value, int role)
{
    if (role == BirthDayRole)
        birthDay = to_date(value.toDate(), "dd.MM.yyyy");
    else if (role == SexRole)
        sex = sexes(value.toInt());
}

}

}
