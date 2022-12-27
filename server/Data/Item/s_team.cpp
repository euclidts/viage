#include "s_team.hpp"

namespace Data
{
s_team::s_team()
    : team_item{}
{
}

const std::string s_team::insert() const
{
    if (caption == "" || companyId <= 0)
        return "";

    return "INSERT INTO Team "
           "(Caption, CompanyId) "
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
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Caption"))
            caption = res.get<std::string>("Caption");
    }
    catch (nanodbc::index_range_error) {}
}

}
