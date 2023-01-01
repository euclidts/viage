#include <server.hpp>
#include "login_flt.hpp"

using namespace drogon;

namespace Data
{
namespace People
{
void login_flt::doFilter(const HttpRequestPtr& req,
                         FilterCallback&& fcb,
                         FilterChainCallback&& fccb)
{
    auto uuid{req->session()->sessionId()};

    if (server::server::get().user_connected(uuid))
    {
        fccb();
        return;
    }

    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k511NetworkAuthenticationRequired);
    fcb(res);
}

}
}
