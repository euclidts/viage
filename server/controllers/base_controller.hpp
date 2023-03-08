#include <drogon/HttpController.h>

#include <server.hpp>

using namespace drogon;

namespace Data
{
template <typename T, typename I, typename F>
struct base_controller : public HttpController<T>
{
    virtual void select(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr&)>&& callback,
                        int foreign_id) const
    {
        I item{};

        LOG_INFO << "select " << item.key;

        F foreign{};
        foreign.id = foreign_id;

        server::server::get().select(req,
                                     callback,
                                     item,
                                     &foreign);
    }

    virtual void update_from(const HttpRequestPtr& req,
                             std::function<void (const HttpResponsePtr&)>&& callback) const
    {
        I item{};

        LOG_INFO << "update from " << item.key;

        Json::Value val{*req->jsonObject()};

        F foreign{};

        if (val.isMember("id") && val["id"].isInt())
            foreign.id = val["id"].asInt();

        item.read(val[item.key]);

        server::server::get().update(req,
                                     callback,
                                     item,
                                     &foreign);
    }
};

}
