#pragma once

#include <drogon/HttpController.h>
#include "list_ctl.hpp"
#include <s_team.hpp>

using namespace drogon;

namespace Data
{
namespace People
{
class team_ctl : public list_ctl<team_ctl, s_team>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(team_ctl::insert, "/companies/teams", Post);
    ADD_METHOD_TO(team_ctl::select, "/companies/{}/teams", Get);
    ADD_METHOD_TO(team_ctl::update, "/companies/{}/teams", Put);
    METHOD_LIST_END

    void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback,
                int parentId) const;
};

}
}
