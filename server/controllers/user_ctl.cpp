#include "user_ctl.hpp"
#include <Data/s_list.hpp>
#include <Data/Item/s_user.hpp>
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
//                                    "FirstName, "
//                                    "LastName, "
                                    "Login, "
                                    "EMail, "
//                                    "Phone, "
                                    "Clearance, "
//                                    "Beneficiary, "
//                                    "Bic, "
//                                    "Iban, "
//                                    "Street, "
//                                    "City, "
//                                    "Canton, "
//                                    "Zip, "
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

    HttpResponsePtr resp;
    auto uuid{req->session()->sessionId()};

    if (server::server::get().user_connected(uuid))
    {
        const auto usr{server::server::get().connected_user(uuid)};

        if (usr.clearance < s_user::Administrator)
        {
            resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k401Unauthorized);
        }
        else
        {
            auto users{nanodbc::execute(server::server::get().connection,
                                        "SELECT "
                                        "Id, "
                                        "FirstName, "
                                        "LastName, "
                                        "Login, "
                                        "EMail, "
                                        "Phone, "
                                        "Clearance, "
                                        "Beneficiary, "
                                        "Bic, "
                                        "Iban, "
                                        "Street, "
                                        "City, "
                                        "Canton, "
                                        "Zip, "
                                        "CompanyId, "
                                        "TeamId, "
                                        "IsLocked "
                                        "FROM [User]")};


            s_list<s_user> list{};
            list.read(users);

            Json::Value json;
            list.write(json);

            std::cout << json;

            resp = HttpResponse::newHttpJsonResponse(json);
        }
    }
    else
    {
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k511NetworkAuthenticationRequired);
    }

    callback(resp);
}

}
}
