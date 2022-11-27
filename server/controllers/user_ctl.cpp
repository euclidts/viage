#include "user_ctl.hpp"

namespace Data
{
namespace People
{
void user_ctl::auth(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 std::string &&userName,
                 const std::string &password)
{
    LOG_DEBUG << "User " << userName << " login";
    // Athneticarion algorithm, read database, verify, identify, etc...

    Json::Value ret;
    ret["result"] = "ok";
    ret["token"] = utils::getUuid();
    auto resp{HttpResponse::newHttpJsonResponse(ret)};
    callback(resp);
}
}
}
