#pragma once

#include <drogon/HttpController.h>
#include "list_ctl.hpp"
#include "nested_item_ctl.hpp"
#include "nested_list_ctl.hpp"
#include <s_contact.hpp>
#include <s_team.hpp>
#include <s_company.hpp>
#include <s_user.hpp>
#include <s_account.hpp>

using namespace drogon;

namespace Data
{
namespace People
{
struct contact_ctl final : public nested_list_ctl<contact_ctl, s_contact, s_account>
{
    METHOD_LIST_BEGIN
//    ADD_METHOD_TO(contact_ctl::insert, "/accounts/contacts", Post);
    ADD_METHOD_TO(contact_ctl::select, "/accounts/{}/contacts", Get);
//    ADD_METHOD_TO(contact_ctl::update_from, "/accounts/contacts", Put);
    METHOD_LIST_END
};

struct company_ctl final : public list_ctl<company_ctl, s_company>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(company_ctl::insert, "/companies", Post);
    ADD_METHOD_TO(company_ctl::select, "/companies", Get);
    ADD_METHOD_TO(company_ctl::update, "/companies", Put);
    METHOD_LIST_END
};

struct team_ctl : public nested_item_ctl<team_ctl, s_team, s_company>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(team_ctl::insert, "/companies/teams", Post);
    ADD_METHOD_TO(team_ctl::select, "/companies/{}/teams", Get);
    ADD_METHOD_TO(team_ctl::update, "/companies/{}/teams", Put);
    METHOD_LIST_END
};

struct user_ctl final : public list_ctl<user_ctl, s_user>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(user_ctl::insert, "/users", Post);
    ADD_METHOD_TO(user_ctl::select, "/users", Get);
    ADD_METHOD_TO(user_ctl::update, "/users", Put);
    METHOD_LIST_END
};

}
}
