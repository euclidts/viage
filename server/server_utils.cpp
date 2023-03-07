#include "server_utils.hpp"
#include <date/date.h>

namespace server
{
namespace utils
{
const std::string clearance_close(const Data::People::s_user& usr)
{
    switch (usr.clearance)
    {
    case Data::People::user_item::Vendor:
        return "AND a.AdvisorId = " + std::to_string(usr.id);
    case Data::People::user_item::Manager:
        return "AND u.TeamId = " + std::to_string(usr.team_id);
    case Data::People::user_item::Director:
        return "AND u.CompanyId = " + std::to_string(usr.company_id);
    default:
        return {};
    }
}

const std::string from_db_date_time(const std::string& db_date_itme)
{
    std::string str{db_date_itme};
    str.erase(str.begin() + str.find_first_of('+') - 1, str.end());
    return str;
}

const std::string from_db_date(const std::string& db_date)
{
    std::string str{db_date};
    str.erase(str.begin() + str.find_first_of(' '), str.end());
    std::istringstream ss{str};
    date::year_month_day ymd;
    ss >> date::parse("%Y-%m-%d", ymd);
    return date::format("%d.%m.%Y", ymd);
}

const std::string to_db_date(const std::string& raw_date, const std::string& format)
{
    std::istringstream ss{raw_date};
    date::year_month_day ymd;
    ss >> date::parse(format, ymd);
    return date::format("%Y-%m-%d", ymd) + " 00:00:00.000000";
}

const std::string update_flag(int flag, const std::string& flag_name, bool set)
{
    std::string str{", "};
    str += flag_name;
    str += set ? "|= " : "&= ~";
    str += std::to_string(flag) +
            " OUTPUT inserted."
            + flag_name;

    return str;
}

}
}
