#ifndef SERVER_HPP
#define SERVER_HPP

#include <json/value.h>
#include <nanodbc/nanodbc.h>

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

private:
    server() {};
};

}
#endif // SERVER_HPP
