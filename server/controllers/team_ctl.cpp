#include "team_ctl.hpp"
#include "s_company.hpp"
#include <s_team.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void team_ctl::insert(const HttpRequestPtr& req,
                      std::function<void (const HttpResponsePtr&)>&& callback,
                      int parentId)
{

}

void team_ctl::select(const HttpRequestPtr& req,
                      std::function<void (const HttpResponsePtr&)>&& callback,
                      int parentId)
{
    LOG_DEBUG << "select team";

    s_company parent{};
    parent.id = parentId;

    s_list<s_team> list{};

    server::server::get().select(req,
                                 callback,
                                 list,
                                 &parent);
}

void team_ctl::update(const HttpRequestPtr& req,
                      std::function<void (const HttpResponsePtr&)>&& callback,
                      int parentId)
{

}

}
}
