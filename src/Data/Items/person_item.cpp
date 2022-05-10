#include <QVariant>

#include "person_item.hpp"

namespace Data
{
namespace People
{
person_item::person_item()
{
}

bool person_item::is_completed() const
{
    if (firstName == "")
        return false;

    if (lastName == "")
        return false;

    if (phone == "")
        return false;

    return true;
}

QHash<int, QByteArray> person_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[FirstNameRole] = "firstName";
    names[LastNameRole] = "lastName";
    names[PhoneRole] = "phone";
    names[EmailRole] = "eMail";

    return names;
}

QVariant person_item::data(int role) const
{
    switch (role)
    {
    case FirstNameRole:
        return QVariant(firstName);
    case LastNameRole:
        return QVariant(lastName);
    case PhoneRole:
        return QVariant(phone);
    case EmailRole:
        return QVariant(eMail);
    }

    return QVariant();
}

void person_item::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case FirstNameRole:
        firstName = value.toString();
        break;
    case LastNameRole:
        lastName = value.toString();
        break;
    case PhoneRole:
        phone = value.toString();
        break;
    case EmailRole:
        eMail = value.toString();
        break;
    }
}

void person_item::read(const QJsonObject& json)
{
    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();

    if (json.contains("firstName") && json["firstName"].isString())
        firstName = json["firstName"].toString();

    if (json.contains("lastName") && json["lastName"].isString())
        lastName = json["lastName"].toString();

    if (json.contains("phone") && json["phone"].isString())
        phone = json["phone"].toString();

    if (json.contains("eMail") && json["eMail"].isString())
        eMail = json["eMail"].toString();
}

void person_item::write(QJsonObject& json) const
{
    json["id"] = id;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    json["phone"] = phone;
    json["eMail"] = eMail;
}

}
}
