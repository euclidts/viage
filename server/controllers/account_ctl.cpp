#include "account_ctl.hpp"
#include <s_account.hpp>
#include <s_user.hpp>
#include <server.hpp>

namespace Data
{
void account_ctl::select(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback) const
{
    LOG_DEBUG << "select account";

    s_list<s_account> list{};

    server::server::get().handle_query(req,
                                       callback,
                                       [&list]
                                       (Json::Value& json, const Data::People::s_user& usr)
    {
        const auto query{s_account::select(usr)};

        if (query == "")
            return false;

        auto result{nanodbc::execute(server::server::get().connection, query)};

        // initialize
        result.next();

        int prev_id{result.get<int>("Id")};

        s_account account{};
        account.read(result);

        Json::Value owners;
        std::vector<s_account> vec{};

        Json::Value tmp;
        tmp["firstName"] = result.get<std::string>("FirstName");
        tmp["lastName"] = result.get<std::string>("LastName");
        owners[0] = tmp;

        // iterate
        while (result.next())
        {
            int id{result.get<int>("Id")};

            if (id != prev_id)
            {
                account.owners = owners;
                owners.clear();
                vec.push_back(account);
                account.read(result);
            }

            tmp["firstName"] = result.get<std::string>("FirstName");
            tmp["lastName"] = result.get<std::string>("LastName");
            owners[owners.size()] = tmp;

            prev_id = id;
        }

        account.owners = owners;
        vec.push_back(account);

        list.set_list(vec);
        list.write(json);

        return true;
    });
}
}
