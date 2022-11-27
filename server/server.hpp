#ifndef SERVER_HPP
#define SERVER_HPP

#include <json/value.h>
#include <nanodbc/nanodbc.h>

namespace server
{
class server
{
public:
    server(const Json::Value& json_config);

    static nanodbc::connection connection;
};
}
#endif // SERVER_HPP
