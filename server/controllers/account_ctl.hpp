#include <drogon/HttpController.h>
#include <s_account.hpp>
#include "list_ctl.hpp"

using namespace drogon;

namespace Data
{
struct account_ctl : public list_ctl<account_ctl, s_account>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(account_ctl::insert, "/accounts", Post);
    ADD_METHOD_TO(account_ctl::select, "/accounts", Get);
    ADD_METHOD_TO(account_ctl::update, "/accounts", Put);
    METHOD_LIST_END

    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback) const override;

    void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback) const override;
};
}
