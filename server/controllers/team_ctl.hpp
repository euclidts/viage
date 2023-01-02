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
    ADD_METHOD_TO(team_ctl::insert, "/Companies/{}/Teams", Post);
    ADD_METHOD_TO(team_ctl::select, "/Companies/{}/Teams", Get);
    ADD_METHOD_TO(team_ctl::update, "/Companies/{}/Teams", Put);
    METHOD_LIST_END

    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback,
                int parentId);

    void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback,
                int parentId);

    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback,
                int parentId);
};

}
}
