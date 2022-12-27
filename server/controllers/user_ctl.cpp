#include "user_ctl.hpp"
#include <s_user.hpp>
#include <s_company.hpp>
#include <s_team.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void user_ctl::auth(const HttpRequestPtr& req,
                    std::function<void (const HttpResponsePtr &)>&& callback,
                    std::string&& userName,
                    const std::string& password,
                    const std::string& format,
                    const std::string& jsonconfig,
                    bool remeberMe)
{
    LOG_DEBUG << "User " << userName << " login";

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
        auto users{nanodbc::execute(server::server::get().connection,
                                    "SELECT "
                                    "Id, "
                                    "Login, "
                                    "EMail, "
                                    "Clearance, "
                                    "CompanyId, "
                                    "TeamId, "
                                    "IsLocked, "
                                    "Password "
                                    "FROM [User]"
                                    "WHERE Login = "
                                    "'" + userName + "'")};

        using namespace utils;

        while (users.next())
        {
            if (users.get<std::string>("Login") == userName
                    && !users.get<int>("IsLocked"))
            {
                const auto pwd{users.get<std::string>("Password")};

                if (binaryStringToHex(reinterpret_cast<const unsigned char*>(pwd.c_str()), pwd.length())
                        == getMd5(password))
                {
                    s_user usr{};
                    usr.read(users);
                    usr.last_access = trantor::Date::date();

                    server::server::get().add_connected_user(usr, uuid);

                    Json::Value json;
                    json["sessionId"] = uuid;
                    json["id"] = usr.id;
                    json["clearance"] = usr.clearance;

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

void user_ctl::get_users(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "get_users";

    server::server::get().get_list<s_user>(req,
                                           callback,
                                           s_user::select(),
                                           s_user::Administrator);
}

void user_ctl::create_user(const HttpRequestPtr &req,
                           std::function<void (const HttpResponsePtr &)>&& callback)
{
    LOG_DEBUG << "create_user";

    const s_user usr{};

    server::server::get().get_list<s_company>(req,
                                              callback,
                                              usr.insert(),
                                              s_user::Administrator);
}

void user_ctl::get_companies(const HttpRequestPtr& req,
                             std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "get_companies";

    server::server::get().get_list<s_company>(req,
                                              callback,
                                              s_company::select(),
                                              s_user::Administrator);
}

void user_ctl::create_company(const HttpRequestPtr& req,
                              std::function<void (const HttpResponsePtr &)>&& callback)
{
    LOG_DEBUG << "create_company";

    s_company cmp;
    cmp.read(*req->jsonObject());

    if (cmp.insert() == "")
    {
        drogon::HttpResponsePtr resp;
        resp->setStatusCode(drogon::k500InternalServerError);
        callback(resp);

        return;
    }

    server::server::get().get_list<s_company>(req,
                                              callback,
                                              cmp.insert(),
                                              s_user::Administrator);
}

void user_ctl::get_teams(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr &)>&& callback,
                         int companyId)
{
    LOG_DEBUG << "get_teams";

    server::server::get().get_list<s_team>(req,
                                              callback,
                                              s_team::select(),
                                              s_user::Administrator);
}

}
}
