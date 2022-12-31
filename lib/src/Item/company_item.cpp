#include <Item/company_item.hpp>

namespace Data
{
company_item::company_item()
    : base_data{}
{
}

void company_item::read(const Json::Value &json)
{
    if (json.isMember("id") && json["id"].isInt())
        id = json["id"].asInt();

    if (json.isMember("name") && json["name"].isString())
        name = json["name"].asString();

    if (json.isMember("teams") && json["teams"].isArray())
        teams = json["teams"];
}

void company_item::write(Json::Value &json) const
{
    json["id"] = id;
    json["name"] = name;
    json["teams"] = teams;
}

bool company_item::is_completed() const
{
    if (name == "")
        return false;

    return true;
}

}
