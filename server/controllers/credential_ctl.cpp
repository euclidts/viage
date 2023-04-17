#include "credential_ctl.hpp"
#include <s_user.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void credential_ctl::auth(const HttpRequestPtr& req,
                          std::function<void (const HttpResponsePtr &)>&& callback,
                          std::string&& userName,
                          const std::string& password,
                          const std::string& format,
                          const std::string& jsonconfig,
                          bool remeberMe)
{
    LOG_INFO << "User " << userName << " login";

    HttpResponsePtr resp;
    auto uuid{req->session()->sessionId()};

    if (server::server::get().user_connected(uuid))
    {
        const auto usr{server::server::get().connected_user(uuid)};

        Json::Value json;
        json["sessionId"] = uuid;
        json["id"] = usr.id;
        json["clearance"] = usr.clearance;

        resp = HttpResponse::newHttpJsonResponse(json);
    }
    else
    {
        auto users{server::server::get().execute(
                                    "SELECT "
                                    "Id, "
                                    "Login, "
                                    "EMail, "
                                    "Clearance, "
                                    "CompanyId, "
                                    "TeamId, "
                                    "IsLocked, "
                                    "Password "
                                    "FROM User "
                                    "WHERE Login = "
                                    "'" + userName + "'")};

        using namespace utils;

        for (auto user : users)
        {
            if (user["Login"].as<std::string>() == userName
                && !user["IsLocked"].as<bool>())
            {
                auto pwd{user["Password"].as<std::string>()};

                if (pwd == getMd5(password))
                {
                    s_user u{};
                    u.set(user);
                    u.last_access = trantor::Date::date();

                    server::server::get().add_connected_user(u, uuid);

                    Json::Value json;
                    json["sessionId"] = uuid;
                    json["id"] = u.id;
                    json["clearance"] = u.clearance;

                    resp = HttpResponse::newHttpJsonResponse(json);
                    break;
                }
            }
        }

        if (!resp)
        {
            resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k401Unauthorized);
        }
    }

    callback(resp);
}

}
}
