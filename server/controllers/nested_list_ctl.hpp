#include <drogon/HttpController.h>

#include "nested_item_ctl.hpp"

using namespace drogon;

namespace Data
{
template <typename T, typename I, typename F>
struct nested_list_ctl : public nested_item_ctl<T, I, F>
{
    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr&)>&& callback,
                int foreign_id) const override
    {
        s_list<I> list{};

        LOG_DEBUG << list.key;

        F foreign{};
        foreign.id = foreign_id;

        Json::Value val{*req->jsonObject()};
        list.read(val[I::key]);

        server::server::get().update(req,
                                     callback,
                                     list,
                                     &foreign);
    }

    virtual void update_from(const HttpRequestPtr& req,
                             std::function<void (const HttpResponsePtr&)>&& callback) const
    {
        s_list<I> list{};

        LOG_DEBUG << list.key;

        Json::Value val{*req->jsonObject()};

        F foreign{};

        if (val.isMember("Id") && val["Id"].isInt())
            foreign.id = val["Id"].asInt();

        list.read(val[list.key]);

        server::server::get().update(req,
                                     callback,
                                     list,
                                     &foreign);
    }
};

}
