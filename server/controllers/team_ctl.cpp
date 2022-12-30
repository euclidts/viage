#include "team_ctl.hpp"
#include <s_team.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void team_ctl::get_teams(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr &)>&& callback,
                         int companyId)
{
    LOG_DEBUG << "get_teams";

    s_list<s_team> list{};

    server::server::get().select(req,
                                 callback,
                                 list,
                                 s_user::Administrator);
}

}
}
