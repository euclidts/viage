#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
namespace People
{
class user_ctl : public HttpController<user_ctl>
{
public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    ADD_METHOD_TO(user_ctl::auth, "/auth?userName={}&password={}", Get, "Data::People::login_flt");
    METHOD_LIST_END

    // your declaration of processing function maybe like this:
    void auth(const HttpRequestPtr& req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string &&userName,
               const std::string &password);
};
}
}
