#include <QVariant>

#include "c_infant.hpp"

namespace Data
{
namespace People
{
c_infant::c_infant()
    : infant_item{}
    , c_person{}
{
}

QHash<int, QByteArray> c_infant::roleNames()
{
    QHash<int, QByteArray> names = c_person::roleNames();

    names[SexRole] = "sex";

    return names;
}

QVariant c_infant::data(int role) const
{
    QVariant base_data{c_person::data(role)};

    if (base_data != QVariant())
        return base_data;

    if (role == SexRole)
        return QVariant(sex);

    return QVariant();
}

void c_infant::setData(const QVariant &value, int role)
{
    c_person::setData(value, role);

    if (role == SexRole)
        sex = senior_citizen_item::sexes(value.toInt());
}

}
}
