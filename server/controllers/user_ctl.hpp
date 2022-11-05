#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
namespace People
{
class user_ctl : public drogon::HttpController<user_ctl>
{
public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    METHOD_ADD(user_ctl::auth, "/auth?userName={}&password={}", Get);
    METHOD_LIST_END

    // your declaration of processing function maybe like this:
    void auth(const HttpRequestPtr& req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string &&userName,
               const std::string &password);
};
}
}
