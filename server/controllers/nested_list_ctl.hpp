#include <drogon/HttpController.h>

#include <s_list.hpp>
#include <server.hpp>
#include "nested_item_ctl.hpp"

using namespace drogon;

namespace Data
{
template <typename T, typename I, typename F>
struct nested_list_ctl : public nested_item_ctl<T, I, F>
{
    void update(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr &)>&& callback,
                        int foreign_id) const override
    {
        LOG_DEBUG << "update " << I::key();

        F foreign{};
        foreign.id = foreign_id;

        Json::Value val{*req->jsonObject()};
        s_list<I> list{};
        list.read(val[I::key()]);

        server::server::get().update(req,
                                     callback,
                                     list,
                                     &foreign);
    }
};

}
