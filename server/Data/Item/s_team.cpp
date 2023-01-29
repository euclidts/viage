#include "s_team.hpp"

namespace Data
{
s_team::s_team()
    : team_item{}
{
}

const std::string s_team::insert(const People::s_user& usr, s_company* foreign) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    if (caption == "" || foreign)
        return {};

    return "INSERT INTO Team "
           "(Caption, CompanyId) "
           "OUTPUT Inserted.Id "
           "VALUES ('"
            + caption +
            "', '"
            + std::to_string(foreign->id) +
            "') ";
}

const std::string s_team::update(const People::s_user& usr, s_company* foreign) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    return "UPDATE Company SET "
           "caption = '"
            + caption +
            "' WHERE Id = "
            + std::to_string(id);
}

void s_team::set(const nanodbc::result &res)
{
    try
    {
        if (!res.is_null("Id"))
            id = res.get<int>("Id");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Caption"))
            caption = res.get<std::string>("Caption");
    }
    catch (...) {}
}

void s_team::read(const Json::Value &json)
{
    team_item::read(json);

    if (json.isMember("CompanyId") && json["CompanyId"].isInt())
        companyId = json["CompanyId"].asInt();
}

}
