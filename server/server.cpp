#include <utility>

#include <drogon/drogon.h>

#include "server.hpp"

#define DEFAULT_TIMEOUT 1200

namespace server
{
server& server::get()
{
    static server instance;
    return instance;
}

void server::init(const Json::Value& json_config)
{
    drogon::app().loadConfigJson(json_config);
    drogon::app().enableSession(DEFAULT_TIMEOUT); // force enable session

    drogon::app().registerBeginningAdvice(
        [this]{
            auto result{execute("UPDATE User Set SessionId = NULL")};
        });

    drogon::app().registerSessionDestroyAdvice(
        [this](const std::string& sessionId){
            LOG_INFO << "Session " << sessionId << " expired";

            execute("UPDATE User Set SessionId = NULL WHERE SessionId = '"
                    + sessionId +
                    "'");
        });

//    drogon::app().registerSessionStartAdvice(
//        [this](const std::string& sessionId){
//            LOG_INFO << "Session " << sessionId << " started";
//        });

    drogon::app().run();
}

drogon::orm::Result server::execute(const std::string &query)
{
    return drogon::app().getDbClient()->execSqlSync(query);
}

void server::execute(const std::vector<std::string> &queries)
{
    for (const auto& query : queries)
        drogon::app().getDbClient()->execSqlSync(query);
}

void server::error_reply(std::function<void (const drogon::HttpResponsePtr &)> &callback)
{
    drogon::HttpResponsePtr resp{drogon::HttpResponse::newHttpResponse()};
    resp->setStatusCode(drogon::k500InternalServerError);
    callback(resp);
}

void server::handle_query(const drogon::HttpRequestPtr& req,
                          std::function<void (const drogon::HttpResponsePtr&)>& callback,
                          const std::function<bool (Json::Value&, const Data::People::s_user&)>& handler)
{
    drogon::HttpResponsePtr resp;
    auto session_id{req->session()->sessionId()};

    auto response{server::server::get().execute(
        "SELECT "
        "Id, "
        "Clearance "
        "FROM User "
        "WHERE SessionId = '"
        + session_id +
        "' AND IsLocked = FALSE")};

    if (response.empty())
    {
        resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k511NetworkAuthenticationRequired);
    }
    else
    {
        Data::People::s_user usr{};
        usr.set(response);

        Json::Value json;

        if (handler(json, usr) && usr.clearance > Data::People::user_item::None)
        {
            resp = drogon::HttpResponse::newHttpJsonResponse(json);
        }
        else
        {
            resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k401Unauthorized);
        }
    }

    callback(resp);
}

std::vector<std::string> server::combine(const std::string& q1, const std::string& q2)
{
    return {q1, q2};
}

std::vector<std::string> server::combine(std::vector<std::string>& q1, const std::string& q2)
{
    q1.emplace_back(q2);
    return q1;
}

}
