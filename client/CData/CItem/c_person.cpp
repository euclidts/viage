#include <QVariant>

#include "c_person.hpp"

namespace Data
{
namespace People
{
c_person::c_person()
    : person_item{}
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
        return QVariant(QString::fromStdString(firstName));
    case LastNameRole:
        return QVariant(QString::fromStdString(lastName));
    case PhoneRole:
        return QVariant(QString::fromStdString(phone));
    case EmailRole:
        return QVariant(QString::fromStdString(eMail));
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
