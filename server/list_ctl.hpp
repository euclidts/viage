#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
template <typename T>
struct list_ctl
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(list_ctl::insert, '/' + T::table, Post);
    ADD_METHOD_TO(list_ctl::select, "/Users", Get);
    ADD_METHOD_TO(list_ctl::update, "/Users", Put);
    METHOD_LIST_END

    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);
};

}
