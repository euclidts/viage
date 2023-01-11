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
    ADD_METHOD_TO(team_ctl::insert, "/companies/{}/teams", Post);
    ADD_METHOD_TO(team_ctl::select, "/companies/{}/teams", Get);
    ADD_METHOD_TO(team_ctl::update, "/companies/{}/teams", Put);
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
