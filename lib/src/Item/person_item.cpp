#include <Item/person_item.hpp>

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

    if (phone.size() <= 3)
        return false;

    return true;
}

void person_item::read(const Json::Value& json)
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

void person_item::write(Json::Value &json) const
{
    json["id"] = id;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    json["phone"] = phone;
    json["eMail"] = eMail;
}

}
}
