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
    if (!json_config.isMember("DB")) return;

    const auto db{json_config["DB"]};

    if (!db.isMember("dbname")
            && !db.isMember("user")
            && !db.isMember("passwd"))
        return;

    connection = nanodbc::connection{db["dbname"].asString(),
            db["user"].asString(),
            db["passwd"].asString()};

    LOG_DEBUG << "Connected with driver " << connection.driver_name()
              << " to database named " << connection.database_name();

    drogon::app().loadConfigJson(json_config);

    if (!json_config.isMember("app"))
    {
        const auto conf{json_config["app"]};

        if (conf.isMember("enable_session")) // force enable session
        {
            if (!conf["enable_session"])
                drogon::app().enableSession(DEFAULT_TIMEOUT);
        }
        else
            drogon::app().enableSession(DEFAULT_TIMEOUT);
    }

    drogon::app().run();
}

bool server::user_connected(const std::string& uuid)
{
    if (const auto it{connected_users.find(uuid)}; it != connected_users.end())
    {
        const auto then{trantor::Date::date().after(- DEFAULT_TIMEOUT)};

        if (it->second.last_access < then)
        {
            remove_connected_user(uuid);
            return false;
        }

        return true;
    }

    return false;
}

Data::People::s_user& server::connected_user(const std::string& uuid) noexcept
{
    return std::get<Data::People::s_user>(*connected_users.find(uuid));
}

void server::add_connected_user(const Data::People::s_user& usr,
                                const std::string& uuid)
{
    if (user_connected(uuid)) return;

    connected_users[uuid] = usr;
}

void server::remove_connected_user(const std::string& uuid)
{
    if (!user_connected(uuid)) return;

    connected_users.erase(uuid);
}

void server::handle_query(const drogon::HttpRequestPtr& req,
                    std::function<void (const drogon::HttpResponsePtr &)>& callback,
                    const std::function<bool (Json::Value &, const Data::People::s_user &)> &handler)
{
    drogon::HttpResponsePtr resp;
    auto uuid{req->session()->sessionId()};

    if (user_connected(uuid))
    {
        const auto usr{connected_user(uuid)};

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
    else
    {
        resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k511NetworkAuthenticationRequired);
    }

    callback(resp);
}

}
