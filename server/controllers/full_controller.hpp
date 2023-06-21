#include <drogon/HttpController.h>

#include <server.hpp>
#include "base_controller.hpp"

using namespace drogon;

namespace Data
{
template <typename T, typename I, typename F, typename C = I>
struct full_controller : public base_controller<T, I, F, C>
{
    virtual void insert(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr&)>&& callback) const
    {
        C item{};

        LOG_INFO << "insert " << item.key;

        Json::Value val{*req->jsonObject()};
        F foreign{};

        if (!(val.isMember(F::foreign_key) && val[F::foreign_key].isInt()))
        {
            server::server::instance().error_reply(callback);
            return;
        }

        foreign.id = val[F::foreign_key].asInt();

        item.read(val);

        server::server::instance().insert(req,
                                     callback,
                                     item,
                                     &foreign);
    }

    virtual void update(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr&)>&& callback,
                        int foreign_id) const
    {
        C item{};

        LOG_INFO << "update " << item.key;

        F foreign{};
        foreign.id = foreign_id;

        Json::Value val{*req->jsonObject()};

        item.read(val[I::key]);

        server::server::instance().update(req,
                                     callback,
                                     item,
                                     &foreign);
    }

    virtual void remove(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr&)>&& callback) const
    {
        C item{};

        LOG_INFO << "remove " << item.key;

        Json::Value val{*req->jsonObject()};

        if (!(val.isMember("id") && val["id"].isInt()))
        {
            server::server::instance().error_reply(callback);
            return;
        }

        item.id = val["id"].asInt();

        server::server::instance().remove(req,
                                     callback,
                                     item);
    }
};

}
