#pragma once

#include <drogon/HttpController.h>
#include <s_team.hpp>
#include <s_company.hpp>
#include <s_user.hpp>
#include <s_account.hpp>
#include <s_owner.hpp>
#include <s_contact.hpp>
#include <s_habitat.hpp>
#include <s_exterior.hpp>
#include "list_ctl.hpp"
#include "full_controller.hpp"

using namespace drogon;

namespace Data
{
namespace Places
{
struct exterior_ctl final : public base_controller<exterior_ctl, s_exterior, s_account>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(exterior_ctl::select, "/accounts/{}/exterior", Get);
    ADD_METHOD_TO(exterior_ctl::update_from, "/accounts/exterior", Put);
    METHOD_LIST_END
};

struct habitat_ctl final : public base_controller<habitat_ctl, s_habitat, s_account>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(habitat_ctl::select, "/accounts/{}/habitat", Get);
    ADD_METHOD_TO(habitat_ctl::update_from, "/accounts/habitat", Put);
    METHOD_LIST_END
};

}
namespace People
{
struct contact_ctl final :
        public full_controller<contact_ctl, s_list<s_contact>, s_account, s_contact>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(contact_ctl::insert, "/accounts/contacts", Post);
    ADD_METHOD_TO(contact_ctl::select, "/accounts/{}/contacts", Get);
    ADD_METHOD_TO(contact_ctl::update_from, "/accounts/contacts", Put);
    METHOD_LIST_END
};

struct owner_ctl final : public full_controller<owner_ctl, s_list<s_owner>, s_account, s_owner>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(owner_ctl::insert, "/accounts/owners", Post);
    ADD_METHOD_TO(owner_ctl::select, "/accounts/{}/owners", Get);
    ADD_METHOD_TO(owner_ctl::update_from, "/accounts/owners", Put);
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

struct team_ctl : public full_controller<team_ctl, s_list<s_team>, s_company, s_team>
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
