#include "s_team.hpp"

namespace Data
{
s_team::s_team()
    : team_item{}
{
}

const std::string s_team::insert(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    if (caption == "" || companyId <= 0)
        return {};

    return "INSERT INTO Team "
           "(Caption, CompanyId) "
           "OUTPUT Inserted.Id "
           "VALUES ('"
            + caption +
            "', '"
            + std::to_string(companyId) +
            "') ";
}

void s_team::read(const nanodbc::result &res)
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

const std::string s_team::update(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    return "UPDATE Company SET "
           "caption = '"
            + caption +
            "' WHERE Id = "
            + std::to_string(id);
}

}
