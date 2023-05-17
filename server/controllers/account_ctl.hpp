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
    ADD_METHOD_TO(account_ctl::search, "/accounts", Get);
    ADD_METHOD_TO(account_ctl::select, "/accountState/{}", Get);
    ADD_METHOD_TO(account_ctl::update, "/accountPPE", Put);
    ADD_METHOD_TO(account_ctl::update, "/accountState", Put);
    ADD_METHOD_TO(account_ctl::remove, "/accounts", Delete);
    METHOD_LIST_END

    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback) const override;

    void search(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback) const override;

    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback) const override;

    void remove(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback) const;
};
}
