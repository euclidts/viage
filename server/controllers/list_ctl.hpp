#include <drogon/HttpController.h>

#include <s_list.hpp>
#include <server.hpp>

using namespace drogon;

namespace Data
{
template <typename T, typename I>
struct list_ctl : public HttpController<T>
{
//    METHOD_LIST_BEGIN
//    ADD_METHOD_TO(list_ctl::insert, std::string{"/"} + s_list<I>::key(), Post);
//    ADD_METHOD_TO(list_ctl::select, std::string{"/"} + s_list<I>::key(), Get);
//    ADD_METHOD_TO(list_ctl::update, std::string{"/"} + s_list<I>::key(), Put);
//    METHOD_LIST_END

    virtual void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback)
    {
        LOG_DEBUG << "insert " << I::key();

        I item{};
        item.read(*req->jsonObject());

        server::server::get().insert(req,
                                     callback,
                                     item);
    }

    virtual void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback)
    {
        LOG_DEBUG << "select " << I::key();

        s_list<I> list{};

        server::server::get().select(req,
                                     callback,
                                     list);
    }

    virtual void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback)
    {
        LOG_DEBUG << "update " << I::key();

        Json::Value val{*req->jsonObject()};
        I item{};
        item.read(val[I::key()]);

        server::server::get().update(req,
                                     callback,
                                     item);
    }
};

}
