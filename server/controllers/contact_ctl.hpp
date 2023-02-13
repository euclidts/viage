#include <drogon/HttpController.h>
#include <s_account.hpp>
#include <s_contact.hpp>
#include "nested_list_ctl.hpp"
#include "list_ctl.hpp"

using namespace drogon;

namespace Data
{
namespace People
{
struct contact_ctl final : public nested_list_ctl<contact_ctl, s_contact, s_account>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(contact_ctl::insert, "/accounts/contacts", Post);
    ADD_METHOD_TO(contact_ctl::select, "/accounts/{}/contacts", Get);
    ADD_METHOD_TO(contact_ctl::update_from, "/accounts/contacts", Put);
    METHOD_LIST_END

    void update_from(const HttpRequestPtr& req,
                     std::function<void (const HttpResponsePtr&)>&& callback) const override;
};

}
}
