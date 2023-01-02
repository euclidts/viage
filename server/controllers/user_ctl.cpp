#include "user_ctl.hpp"
#include <s_user.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void user_ctl::insert(const HttpRequestPtr &req,
                           std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "insert user";

    s_user usr{};

    server::server::get().insert(req,
                                 callback,
                                 usr);
}

void user_ctl::select(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "select user";

    s_list<s_user> list{};

    server::server::get().select(req,
                                 callback,
                                 list);
}

void user_ctl::update(const HttpRequestPtr& req,
                           std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "update user";

    Json::Value val{*req->jsonObject()};
    s_user usr{};
    usr.read(val["user"]);

    server::server::get().update(req,
                                 callback,
                                 usr);
}

}
}
