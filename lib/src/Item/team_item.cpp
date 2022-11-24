#include <Item/team_item.hpp>

namespace Data
{

team_item::team_item()
{
}

void team_item::read(const Json::Value &json)
{
    if (json.isMember("id") && json["id"].isInt())
        id = json["id"].asInt();

    if (json.isMember("caption") && json["caption"].isString())
        caption = json["caption"].asString();

    if (json.isMember("users") && json["users"].isArray())
        has_users = !json["users"].empty();
}

void team_item::write(Json::Value &json) const
{
    json["id"] = id;
    json["caption"] = caption;
}

bool team_item::is_completed() const
{
    if (caption == "")
        return false;

    return true;
}

}
