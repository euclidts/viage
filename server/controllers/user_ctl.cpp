#include "user_ctl.hpp"
#include <s_user.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void user_ctl::create_user(const HttpRequestPtr &req,
                           std::function<void (const HttpResponsePtr &)>&& callback)
{
    LOG_DEBUG << "create_user";

    s_user usr{};

    server::server::get().insert(req,
                                 callback,
                                 usr,
                                 s_user::Administrator);
}

void user_ctl::get_users(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "get_users";

    s_list<s_user> list{};

    server::server::get().select(req,
                                 callback,
                                 list,
                                 s_user::Administrator);
}

void user_ctl::update_user(const HttpRequestPtr& req,
                           std::function<void (const HttpResponsePtr &)>&& callback)
{
    LOG_DEBUG << "update_user";

    Json::Value val{*req->jsonObject()};
    s_user usr{};
    usr.read(val["user"]);

    server::server::get().update(req,
                                 callback,
                                 usr,
                                 s_user::Administrator);
}

}
}
