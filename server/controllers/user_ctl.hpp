#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
namespace People
{
class user_ctl : public HttpController<user_ctl>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(user_ctl::insert, "/users", Post);
    ADD_METHOD_TO(user_ctl::select, "/users", Get);
    ADD_METHOD_TO(user_ctl::update, "/users", Put);
    METHOD_LIST_END

    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);
};

}
}
