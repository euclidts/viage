#pragma once
#include <QVariant>

#include "c_infant.hpp"

namespace Data
{
namespace People
{
template <typename T>
c_infant<T>::c_infant()
    : infant_item<T>{}
    , c_person<T>{}
{
}

template <typename T>
QHash<int, QByteArray> c_infant<T>::roleNames()
{
    QHash<int, QByteArray> names = c_person<T>::roleNames();

    names[SexRole] = "sex";

    return names;
}

template <typename T>
QVariant c_infant<T>::data(int role) const
{
    QVariant base_data{c_person<T>::data(role)};

    if (base_data != QVariant())
        return base_data;

    if (role == SexRole)
        return QVariant(infant_item<T>::sex);

    return QVariant();
}

template <typename T>
void c_infant<T>::setData(const QVariant &value, int role)
{
    c_person<T>::setData(value, role);

    if (role == SexRole)
        infant_item<T>::sex = senior_citizen_item::sexes(value.toInt());
}

}
}
