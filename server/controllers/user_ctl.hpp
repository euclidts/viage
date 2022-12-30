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
    ADD_METHOD_TO(user_ctl::create_user, "/Users", Post);
    ADD_METHOD_TO(user_ctl::get_users, "/Users", Get);
    ADD_METHOD_TO(user_ctl::update_user, "/Users", Put);
    METHOD_LIST_END

    void create_user(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr &)>&& callback);

    void get_users(const HttpRequestPtr& req,
                   std::function<void (const HttpResponsePtr &)>&& callback);

    void update_user(const HttpRequestPtr& req,
                     std::function<void (const HttpResponsePtr &)>&& callback);
};
}
}
