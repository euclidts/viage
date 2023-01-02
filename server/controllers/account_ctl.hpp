#include <drogon/HttpController.h>

using namespace drogon;

namespace Data
{
class account_ctl : public HttpController<account_ctl>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(account_ctl::insert, "/Accounts", Post);
    ADD_METHOD_TO(account_ctl::select, "/Accounts", Get);
    ADD_METHOD_TO(account_ctl::update, "/Accounts", Put);
    METHOD_LIST_END

    void insert(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void select(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);

    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr &)>&& callback);
};

}
