#include <QVariant>

#include "c_person.hpp"

namespace Data
{
namespace People
{
c_person::c_person()
    : person_item{}
    , c_base_item{}
{
}

QHash<int, QByteArray> c_person::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[FirstNameRole] = "firstName";
    names[LastNameRole] = "lastName";
    names[PhoneRole] = "phone";
    names[EmailRole] = "eMail";

    return names;
}

QVariant c_person::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return QVariant(id);
    case FirstNameRole:
        return to_QString(firstName);
    case LastNameRole:
        return to_QString(lastName);
    case PhoneRole:
        return to_QString(phone);
    case EmailRole:
        return to_QString(eMail);
    }

    return QVariant();
}

void c_person::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case FirstNameRole:
        firstName = value.toString().toStdString();
        break;
    case LastNameRole:
        lastName = value.toString().toStdString();
        break;
    case PhoneRole:
        phone = value.toString().toStdString();
        break;
    case EmailRole:
        eMail = value.toString().toStdString();
        break;
    }
}

}
}
