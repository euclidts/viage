#include "account_ctl.hpp"
#include <s_account.hpp>
#include <s_user.hpp>
#include <s_document.hpp>
#include <server.hpp>

namespace Data
{
void account_ctl::insert(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback) const
{
    LOG_INFO << "insert account";

    s_account item{};

    server::server::get().insert(req,
                                 callback,
                                 item);
}

void account_ctl::search(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback) const
{
    LOG_INFO << "search accounts";

    s_list<s_account> list{};

    server::server::get().handle_query(req,
                                       callback,
                                       [&list]
                                       (Json::Value& json, const Data::People::s_user& usr)
    {
        const auto query{s_account::search(usr)};

        if (query == "")
            return false;

        auto result{server::server::get().execute(query)};

        if (!result.empty()) // handle potentialy empty list
        {
            // initialize
            int prev_id{result.front()["Id"].as<int>()};

            s_account account{};
            account.set(result.front());

            Json::Value owners;
            std::vector<s_account> vec{};

            Json::Value tmp;
            tmp["firstName"] = result.front()["FirstName"].isNull() ?
                                   "" :
                                   result.front()["FirstName"].as<std::string>();
            tmp["lastName"] = result.front()["LastName"].isNull() ?
                                  "" :
                                  result.front()["LastName"].as<std::string>();
            owners[0] = tmp;

            // iterate
            for (const auto row : result)
            {
                int id{row["Id"].as<int>()};

                if (id != prev_id)
                {
                    account.owners = owners;
                    owners.clear();
                    vec.push_back(account);
                    account.clear();
                    account.set(row);
                }

                tmp["firstName"] = row["FirstName"].isNull() ?
                                       "" :
                                       row["FirstName"].as<std::string>();
                tmp["lastName"] = row["LastName"].isNull() ?
                                      "" :
                                      row["LastName"].as<std::string>();
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

void account_ctl::remove(const HttpRequestPtr& req,
                         std::function<void (const HttpResponsePtr&)>&& callback) const
{
    LOG_INFO << "remove account";

    Json::Value val{*req->jsonObject()};

    if (!(val.isMember("id") && val["id"].isInt()))
    {
        server::server::get().error_reply(callback);
        return;
    }

    s_account item{};
    item.id = val["id"].asInt();

    auto result{server::server::get().execute(
        "SELECT RelativePath, FileName, Extension FROM Document "
        "WHERE AccountId = "
        + std::to_string(item.id))};

    s_document doc{};

    for (const auto row : result)
    {
        doc.set(row);
        const auto path{doc.get_path()};
        if (!path.empty()) std::filesystem::remove(path);
        doc.clear();
    }

    server::server::get().execute(
                     "DELETE FROM Document "
                     "WHERE AccountId = "
                     + std::to_string(item.id) +
                     "; DELETE FROM BaseOwner "
                     "WHERE InfantAccountId = "
                     + std::to_string(item.id) +
                     " OR OwnerAccountId = "
                     + std::to_string(item.id));

    server::server::get().remove(req,
                                 callback,
                                 item);

}
}
