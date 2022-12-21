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

    template <typename T>
    void get_list(const drogon::HttpRequestPtr& req,
                  std::function<void (const drogon::HttpResponsePtr&)>& callback,
                  const std::string& query,
                  const Data::People::s_user::clearances& min_clearance
                  = Data::People::s_user::None)
    {
        drogon::HttpResponsePtr resp;
        auto uuid{req->session()->sessionId()};

        if (user_connected(uuid))
        {
            const auto usr{connected_user(uuid)};

            if (usr.clearance < min_clearance)
            {
                resp = drogon::HttpResponse::newHttpResponse();
                resp->setStatusCode(drogon::k401Unauthorized);
            }
            else
            {
                auto table{nanodbc::execute(connection, query)};

                Data::s_list<T> list{};
                list.read(table);

                Json::Value json;
                list.write(json);

                resp = drogon::HttpResponse::newHttpJsonResponse(json);
            }
        }
        else
        {
            resp = drogon::HttpResponse::newHttpResponse();
            resp->setStatusCode(drogon::k511NetworkAuthenticationRequired);
        }

        callback(resp);
    }

private:
    server() {}

    std::map<std::string, Data::People::s_user> connected_users;
};

}

#endif // SERVER_HPP
