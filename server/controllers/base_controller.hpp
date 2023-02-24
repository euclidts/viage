#include <drogon/HttpController.h>

#include <server.hpp>

using namespace drogon;

namespace Data
{
template <typename T, typename I, typename F>
struct base_controller : public HttpController<T>
{
    template <typename C>
    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback) const
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

    template <typename C>
    void update(const HttpRequestPtr& req,
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

        if (val.isMember("Id") && val["Id"].isInt())
            foreign.id = val["Id"].asInt();

        item.read(val[item.key]);

        server::server::get().update(req,
                                     callback,
                                     item,
                                     &foreign);
    }
};

}
