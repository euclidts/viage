#include "company_item.hpp"
#include "team_item.hpp"

#include <List/item_list.hpp>

namespace Data
{
company_item::company_item()
    : base_data{}
{
}

bool company_item::update(item_list<team_item>* ti)
{
    Json::Value arr{};
    ti->write(arr);
    if (teams == arr)
        return false;

    teams = arr;
    return true;
}

Json::Value company_item::get(item_list<team_item> *ti) const
{
    return teams;
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
