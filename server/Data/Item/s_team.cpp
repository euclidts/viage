#include "s_team.hpp"

namespace Data
{
s_team::s_team()
    : team_item{}
{
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
