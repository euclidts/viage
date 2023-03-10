#include <drogon/HttpController.h>

#include <server.hpp>
#include "base_controller.hpp"

using namespace drogon;

namespace Data
{
template <typename T, typename I, typename F, typename C = I>
struct full_controller : public base_controller<T, I, F>
{
    virtual void insert(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr&)>&& callback) const
    {
        C item{};

        LOG_INFO << "insert " << item.key;

        Json::Value val{*req->jsonObject()};

        F foreign{};

        if (val.isMember(F::foreign_key) && val[F::foreign_key].isInt())
            foreign.id = val[F::foreign_key].asInt();

        item.read(val);

        server::server::get().insert(req,
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

        server::server::get().update(req,
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
        item.id = val["id"].asInt();

        server::server::get().remove(req,
                                     callback,
                                     item);
    }
};

}
