#include <drogon/drogon.h>

#include "server.hpp"

using namespace std;

namespace server
{
server::server(const Json::Value& json_config)
{
    if (!json_config.isMember("DB")) return;

    const auto db{json_config["DB"]};

    if (!db.isMember("dbname")
            && !db.isMember("user")
            && !db.isMember("passwd"))
        return;

    connection.connect(db["dbname"].asString(),
            db["user"].asString(),
            db["passwd"].asString());

    cout << "Connected with driver " << connection.driver_name() << endl;

    drogon::app().loadConfigJson(json_config);
    drogon::app().run();

}

nanodbc::connection server::connection{};

}