#pragma once
#include <drogon/HttpController.h>

#include <s_list.hpp>
#include <server.hpp>

using namespace drogon;

namespace Data
{
template <typename T, typename I, typename F>
struct nested_item_ctl : public HttpController<T>
{
    virtual void insert(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr &)>&& callback) const
    {
        LOG_DEBUG << I::key;

        Json::Value val{*req->jsonObject()};

        F foreign{};

        if (val.isMember(F::foreign_key) && val[F::foreign_key].isInt())
            foreign.id = val[F::foreign_key].asInt();

        I item{};
        item.read(val);

        server::server::get().insert(req,
                                     callback,
                                     item,
                                     &foreign);
    }

    virtual void select(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr&)>&& callback,
                        int foreign_id) const
    {
        s_list<I> list{};

        LOG_DEBUG << list.key;

        F foreign{};
        foreign.id = foreign_id;

        server::server::get().select(req,
                                     callback,
                                     list,
                                     &foreign);
    }

    virtual void update(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr &)>&& callback,
                        int foreign_id) const
    {
        LOG_DEBUG << I::key;

        F foreign{};
        foreign.id = foreign_id;

        Json::Value val{*req->jsonObject()};
        I item{};
        item.read(val[I::key]);

        server::server::get().update(req,
                                     callback,
                                     item,
                                     &foreign);
    }
};

}
