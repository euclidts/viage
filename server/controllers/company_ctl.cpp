#include "company_ctl.hpp"
#include <s_company.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void company_ctl::insert(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "insert company";

    s_company cmp;
    cmp.read(*req->jsonObject());

//    if (cmp.insert().empty())
//    {
//        drogon::HttpResponsePtr resp;
//        resp->setStatusCode(drogon::k500InternalServerError);
//        callback(resp);

//        return;
//    }

    server::server::get().insert(req,
                                 callback,
                                 cmp);
}

void company_ctl::select(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "select company";

    s_list<s_company> list{};

    server::server::get().select(req,
                                 callback,
                                 list);
}

void company_ctl::update(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "update company";

    Json::Value val{*req->jsonObject()};
    s_company cmp{};
    cmp.read(val["company"]);

    server::server::get().update(req,
                                 callback,
                                 cmp);
}

}
}
