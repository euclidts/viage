#include "server_utils.hpp"

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

}
}
