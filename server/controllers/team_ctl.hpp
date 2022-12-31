#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
namespace People
{
class team_ctl : public HttpController<team_ctl>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(team_ctl::create_teams, "/Companies/{}/Teams", Post);
    ADD_METHOD_TO(team_ctl::get_teams, "/Companies/{}/Teams", Get);
    ADD_METHOD_TO(team_ctl::update_teams, "/Companies/{}/Teams", Put);
    METHOD_LIST_END

    void create_teams(const HttpRequestPtr& req,
                   std::function<void (const HttpResponsePtr &)>&& callback,
                   int parentId);

    void get_teams(const HttpRequestPtr& req,
                   std::function<void (const HttpResponsePtr &)>&& callback,
                   int parentId);

    void update_teams(const HttpRequestPtr& req,
                   std::function<void (const HttpResponsePtr &)>&& callback,
                   int parentId);
};
}
}
