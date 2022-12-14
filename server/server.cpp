#include <drogon/drogon.h>

#include "server.hpp"

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
    drogon::app().run();
}
}
