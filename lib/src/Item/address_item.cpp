#include <Item/address_item.hpp>

namespace Data
{
namespace Places
{
address_item::address_item()
    : base_data()
{
}

void address_item::read(const Json::Value& json)
{
    if (json.isMember("street") && json["street"].isString())
        street = json["street"].asString();

    if (json.isMember("zip") && json["zip"].isInt())
        zip = json["zip"].asInt();

    if (json.isMember("canton") && json["canton"].isString())
        canton = json["canton"].asString();

    if (json.isMember("city") && json["city"].isString())
        city = json["city"].asString();
}

void address_item::write(Json::Value &json) const
{
    json["street"] = street;
    json["zip"] = zip;
    json["canton"] = canton;
    json["city"] = city;
}

bool address_item::is_completed() const
{
    if (street == "")
        return false;

    if (city == "")
        return false;

    return true;
}

}
}
