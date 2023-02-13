#include <Item/owner_item.hpp>

namespace Data
{
namespace People
{
owner_item::owner_item()
    : infant_item()
    , address{new Places::address_item}
{
}

void owner_item::read(const Json::Value &json)
{
    infant_item::read(json);

    if (json.isMember("birthDay") && json["birthDay"].isString())
        if (!json["birthDay"].asString().empty())
            birthDay = json["birthDay"].asString();

    if (json.isMember("civilStatus") && json["civilStatus"].isInt())
        civilStatus = civilStates(json["civilStatus"].asInt());

    if (json.isMember("avs") && json["avs"].isString())
        avs = json["avs"].asString();

    if (json.isMember("address") && json["address"].isObject())
        address->read(json["address"]);
}

void owner_item::write(Json::Value &json) const
{
    infant_item::write(json);

    json["birthDay"] = birthDay;
    json["civilStatus"] = civilStatus;
    json["avs"] = avs;

    Json::Value jsonAddress;
    address->write(jsonAddress);

    json["address"] = jsonAddress;
}

bool owner_item::is_completed() const
{
    if (!infant_item::is_completed())
        return false;

    if (civilStatus == None)
        return false;

    if (avs == "")
        return false;

    if (!address->is_completed())
        return false;

    return true;
}

}
}
