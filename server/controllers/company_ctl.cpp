#include "company_ctl.hpp"
#include <s_company.hpp>
#include <server.hpp>

namespace Data
{
namespace People
{
void company_ctl::get_companies(const HttpRequestPtr& req,
                                std::function<void (const HttpResponsePtr&)>&& callback)
{
    LOG_DEBUG << "get_companies";

    s_list<s_company> list{};

    server::server::get().select(req,
                                 callback,
                                 list,
                                 s_user::Administrator);
}

void company_ctl::create_company(const HttpRequestPtr& req,
                                 std::function<void (const HttpResponsePtr &)>&& callback)
{
    LOG_DEBUG << "create_company";

    s_company cmp;
    cmp.read(*req->jsonObject());

    if (cmp.insert().empty())
    {
        drogon::HttpResponsePtr resp;
        resp->setStatusCode(drogon::k500InternalServerError);
        callback(resp);

        return;
    }

    server::server::get().insert(req,
                                 callback,
                                 cmp,
                                 s_user::Administrator);
}

}
}
