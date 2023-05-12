#ifndef SERVER_HPP
#define SERVER_HPP

#include <drogon/orm/Result.h>
#include <json/value.h>
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
    void init(const Json::Value& usr_config);

    server(server const&) = delete;
    void operator = (server const&) = delete;

    bool user_connected(const std::string& uuid);
    Data::People::s_user& connected_user(const std::string& uuid) noexcept;
    void add_connected_user(const Data::People::s_user& usr, const std::string& uuid);
    void remove_connected_user(const std::string& uuid);

    drogon::orm::Result execute(const std::string& query);

    void error_reply(std::function<void (const drogon::HttpResponsePtr& )>& callback);

    void handle_query(const drogon::HttpRequestPtr& req,
                      std::function<void (const drogon::HttpResponsePtr&)>& callback,
                      const std::function<bool (Json::Value&, const Data::People::s_user&)>& handler);

    template <typename T, typename ...Foreign>
    void insert(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                const T& item,
                const Foreign*... foreign)
    {
        handle_query(req,
                     callback,
                     [this, &item, ... args = foreign]
                     (Json::Value& json, const Data::People::s_user& usr)
        {
            const auto query{item.insert(usr, args...)};

            if (query.empty()) return false;

            try
            {
                auto result{execute(query)};
                json["id"] = result.front()["Id"].template as<int>();
                json["success"] = true;
            }
            catch (...)
            {
                json["success"] = false;
            }

            return true;
        });
    }

    template <typename T, typename ...Foreign>
    void search(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                T& item,
                const Foreign*... foreign)
    {
        handle_query(req,
                     callback,
                     [this, &item, ... args = foreign]
                     (Json::Value& json, const Data::People::s_user& usr)
        {
            const auto query{T::search(usr, args...)};

            if (query.empty()) return false;

            auto result{execute(query)};

            item.set(result);
            item.write(json);

            return true;
        });
    }

    template <typename T, typename ...Foreign>
    void select(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                T& item,
                const Foreign*... foreign)
    {
        handle_query(req,
                     callback,
                     [this, &item, ... args = foreign]
                     (Json::Value& json, const Data::People::s_user& usr)
        {
            const auto query{item.select(usr, args...)};

            if (query.empty()) return false;

            auto result{execute(query)};

            item.set(result);
            item.write(json);

            return true;
        });
    }

    template <typename T, typename ...Foreign>
    void update(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                const T& item,
                const Foreign*... foreign)
    {
        handle_query(req,
                     callback,
                     [this, &item, ... args = foreign]
                     (Json::Value& json, const Data::People::s_user& usr)
        {
            auto query{item.update(usr, args...)};

            if (query.empty()) return false;

            T::foreign_update(query,
                              item.is_completed(),
                              args...);

            try
            {
                auto result{execute(query)};
                json["success"] = true;
                T::update_reply(result, json, args...);
            }
            catch (...)
            {
                json["success"] = false;
            }

            return true;
        });
    }

    template <typename T, typename ...Foreign>
    void remove(const drogon::HttpRequestPtr& req,
                std::function<void (const drogon::HttpResponsePtr&)>& callback,
                const T& item,
                const Foreign*... foreign)
    {
        handle_query(req,
                     callback,
                     [this, &item, ... args = foreign]
                     (Json::Value& json, const Data::People::s_user& usr)
        {
            auto query{item.remove(usr, args...)};

            if (query.empty()) return false;

            try
            {
                auto result{execute(query)};
                json["success"] = true;
            }
            catch (...)
            {
                json["success"] = false;
            }

            return true;
        });
    }

private:
    server() {}

    std::map<std::string, Data::People::s_user> connected_users;
};

}

#endif // SERVER_HPP
