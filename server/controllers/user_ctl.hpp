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
    ADD_METHOD_TO(user_ctl::auth, "/auth?userName={}&password={}", Get);
    ADD_METHOD_TO(user_ctl::auth, "/auth?userName={}&password={}&format={}&jsconfig={}&rememberMe={}", Get);
    ADD_METHOD_TO(user_ctl::get_users, "/Users", Get);
    ADD_METHOD_TO(user_ctl::get_companies, "/Companies", Get);
    ADD_METHOD_TO(user_ctl::get_teams, "/Companies/{}/Teams", Get);
    METHOD_LIST_END

    void auth(const HttpRequestPtr& req,
              std::function<void (const HttpResponsePtr &)>&& callback,
              std::string&& userName,
              const std::string& password,
              const std::string& format = "",
              const std::string& jsonconfig = "",
              bool remeberMe = false);

    void get_users(const HttpRequestPtr& req,
                   std::function<void (const HttpResponsePtr &)>&& callback);

    void get_companies(const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)>&& callback);

    void get_teams(const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)>&& callback,
                       int companyId);
};
}
}
