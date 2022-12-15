#ifndef SERVER_HPP
#define SERVER_HPP

#include <json/value.h>
#include <nanodbc/nanodbc.h>
#include <drogon/utils/Utilities.h>

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

    bool user_connected(const std::string& uuid) const;
    std::map<std::string, Data::People::s_user>::iterator connected_user(const std::string& uuid);
    void add_connected_user(const Data::People::s_user& usr, const std::string& uuid);
    void remove_connected_user(const std::string& uuid);

private:
    server() {}

    std::map<std::string, Data::People::s_user> connected_users;
};

}
#endif // SERVER_HPP
