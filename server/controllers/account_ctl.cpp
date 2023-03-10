#include "account_ctl.hpp"
#include <s_account.hpp>
#include <s_user.hpp>
#include <s_document.hpp>
#include <server.hpp>

namespace Data
{
void account_ctl::insert(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr &)>&& callback) const
{
    LOG_INFO << "account";

    s_account item{};

    server::server::get().insert(req,
                                 callback,
                                 item);
}

void account_ctl::select(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback) const
{
    LOG_INFO << "accounts";

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

        if (result.next()) // handle potentialy empty list
        {
            // initialize
            int prev_id{result.get<int>("Id")};

            s_account account{};
            account.set(result);

            Json::Value owners;
            std::vector<s_account> vec{};

            Json::Value tmp;
            tmp["firstName"] = result.get<std::string>("FirstName", "");
            tmp["lastName"] = result.get<std::string>("LastName", "");
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
                    account.clear();
                    account.set(result);
                }

                tmp["firstName"] = result.get<std::string>("FirstName", "");
                tmp["lastName"] = result.get<std::string>("LastName", "");
                owners[owners.size()] = tmp;

                prev_id = id;
            }

            account.owners = owners;
            vec.push_back(account);

            list.set_list(vec);
            list.write(json);
        }

        return true;
    });
}

void account_ctl::remove(const HttpRequestPtr &req,
                         std::function<void (const HttpResponsePtr&)>&& callback) const
{
    LOG_INFO << "account";

    Json::Value val{*req->jsonObject()};

    if (!(val.isMember("id") && val["id"].isInt()))
    {
        server::server::get().error_reply(callback);
        return;
    }

    s_account item{};
    item.id = val["id"].asInt();

    auto result{nanodbc::execute(server::server::get().connection,
                                 "SELECT RelativePath FileName Extension FROM Document "
                                 "WHERE AccountId = "
                                 + to_string(item.id))};

    s_document doc{};

    while (result.next())
    {
        doc.set(result);
        filesystem::remove(doc.get_path());
        doc.clear();
    }

    nanodbc::execute(server::server::get().connection,
                     "DELETE FROM Document "
                     "WHERE AccountId = "
                     + to_string(item.id) +
                     "; DELETE FROM BaseOwner "
                     "WHERE InfantAccountId = "
                     + to_string(item.id) +
                     " OR WHERE OwnerAccountId = "
                     + to_string(item.id));

    server::server::get().remove(req,
                                 callback,
                                 item);

}
}
