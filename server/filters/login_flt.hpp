#pragma once

#include <drogon/HttpFilter.h>

using namespace drogon;

namespace Data
{
namespace People
{
class login_flt : public HttpFilter<login_flt>
{
  public:
    login_flt() {}
    void doFilter(const HttpRequestPtr &req,
                  FilterCallback &&fcb,
                  FilterChainCallback &&fccb) override;
};
}
}
