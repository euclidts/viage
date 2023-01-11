#pragma once
#include <QVariant>

#include "c_person.hpp"
#include <utils.hpp>

using namespace Utils;

namespace Data
{
namespace People
{
template <typename T>
c_person<T>::c_person()
    : person_item<T>{}
{
}

template <typename T>
QHash<int, QByteArray> c_person<T>::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[FirstNameRole] = "firstName";
    names[LastNameRole] = "lastName";
    names[PhoneRole] = "phone";
    names[EmailRole] = "eMail";

    return names;
}

template <typename T>
QVariant c_person<T>::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return QVariant(person_item<T>::id);
    case FirstNameRole:
        return to_QString(person_item<T>::firstName);
    case LastNameRole:
        return to_QString(person_item<T>::lastName);
    case PhoneRole:
        return to_QString(person_item<T>::phone);
    case EmailRole:
        return to_QString(person_item<T>::eMail);
    }

    return QVariant();
}

template <typename T>
void c_person<T>::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case FirstNameRole:
        person_item<T>::firstName = value.toString().toStdString();
        break;
    case LastNameRole:
        person_item<T>::lastName = value.toString().toStdString();
        break;
    case PhoneRole:
        person_item<T>::phone = value.toString().toStdString();
        break;
    case EmailRole:
        person_item<T>::eMail = value.toString().toStdString();
        break;
    }
}

}
}
