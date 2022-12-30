#ifndef SERVER_HPP
#define SERVER_HPP

#include <json/value.h>
#include <nanodbc/nanodbc.h>
#include <drogon/utils/Utilities.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

#include <Data/Item/s_user.hpp>
#include <s_list.hpp>

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

    bool user_connected(const std::string& uuid);
    Data::People::s_user& connected_user(const std::string& uuid) noexcept;
    void add_connected_user(const Data::People::s_user& usr, const std::string& uuid);
    void remove_connected_user(const std::string& uuid);


    void handle_query(const drogon::HttpRequestPtr& req,
                      std::function<void (const drogon::HttpResponsePtr&)>& callback,
                      const std::function<void (Json::Value&)>& handler,
                      const Data::People::s_user::clearances& min_clearance
                      = Data::People::s_user::None);

    template <typename T>
    void insert(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                const T& item,
                const Data::People::s_user::clearances& min_clearance
                = Data::People::s_user::None)
    {
        handle_query(req,
                     callback,
                     [this, item](Json::Value& json)
        {
            try
            {
                auto result{nanodbc::execute(connection, item.insert())};
                result.next();
                json["id"] = result.template get<int>(0);
                json["success"] = true;
            }
            catch (...)
            {
                json["success"] = false;
            }
        },
        min_clearance);
    }

    template <typename T>
    void select(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                T& item,
                const Data::People::s_user::clearances& min_clearance
                = Data::People::s_user::None)
    {
        handle_query(req,
                     callback,
                     [this, &item](Json::Value& json)
        {
            auto result{nanodbc::execute(connection, T::select())};

            item.read(result);
            item.write(json);
        },
        min_clearance);
    }

    template <typename T>
    void update(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                const T& item,
                const Data::People::s_user::clearances& min_clearance
                = Data::People::s_user::None)

    {
        handle_query(req,
                     callback,
                     [this, item](Json::Value& json)
        {
            try
            {
                const auto result{nanodbc::execute(connection, item.update())};
                json["success"] = true;
            }
            catch (...)
            {
                json["success"] = false;
            }
        },
        min_clearance);
    }

private:
    server() {}

    std::map<std::string, Data::People::s_user> connected_users;
};

}

#endif // SERVER_HPP
