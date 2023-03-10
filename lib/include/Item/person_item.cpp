#pragma once
#include <Item/person_item.hpp>

namespace Data
{
namespace People
{
template <typename T>
person_item<T>::person_item()
{
}

template <typename T>
bool person_item<T>::is_completed() const
{
    if (firstName == "")
        return false;

    if (lastName == "")
        return false;

    if (phone.size() <= 10)
        return false;

    return true;
}

template <typename T>
void person_item<T>::read(const Json::Value& json)
{
    if (json.isMember("id") && json["id"].isInt())
        id = json["id"].asInt();

    if (json.isMember("firstName") && json["firstName"].isString())
        firstName = json["firstName"].asString();

    if (json.isMember("lastName") && json["lastName"].isString())
        lastName = json["lastName"].asString();

    if (json.isMember("phone") && json["phone"].isString())
        phone = json["phone"].asString();

    if (json.isMember("eMail") && json["eMail"].isString())
        eMail = json["eMail"].asString();
}

template <typename T>
void person_item<T>::write(Json::Value &json) const
{
    json["id"] = id;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    json["phone"] = phone;
    json["eMail"] = eMail;
}

}
}
