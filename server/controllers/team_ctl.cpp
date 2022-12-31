#include "team_ctl.hpp"
#include "s_company.hpp"
#include <s_team.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void team_ctl::create_teams(const HttpRequestPtr& req,
                            std::function<void (const HttpResponsePtr&)>&& callback,
                            int parentId)
{

}

void team_ctl::get_teams(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback,
                         int parentId)
{
    LOG_DEBUG << "get_teams";

    s_company parent{};
    parent.id = parentId;

    s_list<s_team> list{};

    server::server::get().select(req,
                                 callback,
                                 list,
                                 parent,
                                 s_user::Administrator);
}

void team_ctl::update_teams(const HttpRequestPtr& req,
                            std::function<void (const HttpResponsePtr&)>&& callback,
                            int parentId)
{

}

}
}
