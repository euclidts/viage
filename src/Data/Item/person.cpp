#include <QVariant>

#include "person.hpp"

namespace Data
{
namespace People
{
person::person()
    : base_item<person>{}
    , phone{"+41"}
{}

QHash<int, QByteArray> person::roleNames()
{
    QHash<int, QByteArray> names;

    names[IdRole] = "id";
    names[FirstNameRole] = "firstName";
    names[LastNameRole] = "lastName";
    names[PhoneRole] = "phone";
    names[EmailRole] = "eMail";

    return names;
}

QVariant person::data(int role) const
{
    switch (role)
    {
    case IdRole:
        return id;
    case FirstNameRole:
        return firstName;
    case LastNameRole:
        return lastName;
    case PhoneRole:
        return phone;
    case EmailRole:
        return eMail;
    }

    return QVariant{};
}

void person::setData(const QVariant& value, int role)
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

void person::read(const QJsonObject& json)
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

void person::write(QJsonObject& json) const
{
    json["id"] = id;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    json["phone"] = phone;
    json["eMail"] = eMail;
}

bool person::is_completed() const
{
    if (firstName == "")
        return false;

    if (lastName == "")
        return false;

    if (phone.size() <= 3)
        return false;

    return true;
}

}
}
