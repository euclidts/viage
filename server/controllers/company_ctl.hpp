#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
namespace People
{
class company_ctl : public HttpController<company_ctl>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(company_ctl::create_company, "/Companies", Post);
    ADD_METHOD_TO(company_ctl::get_companies, "/Companies", Get);
    ADD_METHOD_TO(company_ctl::update_company, "/Companies", Put);
    METHOD_LIST_END

    void create_company(const HttpRequestPtr& req,
                        std::function<void (const HttpResponsePtr &)>&& callback);

    void get_companies(const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)>&& callback);

    void update_company(const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)>&& callback);
};
}
}
