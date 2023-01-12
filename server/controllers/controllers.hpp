#pragma once

#include "list_ctl.hpp"
#include <s_company.hpp>
#include <s_user.hpp>
#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
namespace People
{
struct company_ctl : public list_ctl<company_ctl, s_company>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(company_ctl::insert, "/companies", Post);
    ADD_METHOD_TO(company_ctl::select, "/companies", Get);
    ADD_METHOD_TO(company_ctl::update, "/companies", Put);
    METHOD_LIST_END
};

struct user_ctl : public list_ctl<user_ctl, s_user>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(user_ctl::insert, "/users", Post);
    ADD_METHOD_TO(user_ctl::select, "/users", Get);
    ADD_METHOD_TO(user_ctl::update, "/users", Put);
    METHOD_LIST_END
};

}
}
