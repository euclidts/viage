#ifndef SERVER_HPP
#define SERVER_HPP

#include <json/value.h>
#include <nanodbc/nanodbc.h>
#include <trantor/utils/Date.h>

#include <Data/Item/s_user.hpp>

namespace server
{
class server
{
public:
    static server& get();
    void init(const Json::Value& json_config);

    server(server const&) = delete;
    void operator = (server const&) = delete;

    nanodbc::connection connection;

//    std::map<std::string, std::pair<trantor::Date, Data::People::s_user>> conected_users;

private:
    server() {};
};

}
#endif // SERVER_HPP
