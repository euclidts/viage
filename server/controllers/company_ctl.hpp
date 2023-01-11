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
    ADD_METHOD_TO(company_ctl::insert, "/companies", Post);
    ADD_METHOD_TO(company_ctl::select, "/companies", Get);
    ADD_METHOD_TO(company_ctl::update, "/companies", Put);
    METHOD_LIST_END

    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);
};

}
}
