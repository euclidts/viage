#include <QVariant>

#include "c_contact.hpp"

namespace Data
{
namespace People
{
c_contact::c_contact()
    : c_infant{}
    , contact_item{}
{
}

QHash<int, QByteArray> c_contact::roleNames()
{
    QHash<int, QByteArray> names = c_infant::roleNames();

    names[IsInfantRole] = "isInfant";

    return names;
}

QVariant c_contact::data(int role) const
{
    QVariant base_data{c_infant::data(role)};

    if (base_data != QVariant())
        return base_data;

    if (role == IsInfantRole)
        return QVariant(isInfant);

    return QVariant();
}

void c_contact::setData(const QVariant &value, int role)
{
    c_infant::setData(value, role);

    if (role == IsInfantRole)
        isInfant = value.toBool();
}

}
}
