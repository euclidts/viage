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
    LOG_INFO << "User " << userName << " signing in";

    HttpResponsePtr resp;
    auto session_id{req->session()->sessionId()};

    auto response{server::server::get().execute(
        "SELECT "
        "Id, "
        "Login, "
        "Clearance, "
        "IsLocked, "
        "Password,"
        "SessionId "
        "FROM User "
        "WHERE Login = "
        "'" + userName + "'")};

    if (response.empty())
    {
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k404NotFound);
        callback(resp);
        return;
    }

    s_user user{};
    user.set(response);

    if (user.isLocked ||
        response.front()["Password"].as<std::string>() != utils::getMd5(password))
    {
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k403Forbidden);
        callback(resp);
        return;
    }

    if (response.front()["SessionId"].isNull())
    {
        server::server::get().execute("UPDATE User SET SessionId = '"
                                      + session_id +
                                      "' WHERE Id = "
                                      + std::to_string(user.id));
    }

    Json::Value json;
    json["sessionId"] = session_id;
    json["id"] = user.id;
    json["clearance"] = user.clearance;

    resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
}
}
