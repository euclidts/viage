#include <fstream>

#include <drogon/HttpAppFramework.h>
#include <drogon/utils/Utilities.h>

#include "document_ctl.hpp"
#include <s_user.hpp>
#include <server.hpp>

namespace Data
{
void document_ctl::update(const HttpRequestPtr& req,
                          std::function<void (const HttpResponsePtr&)>&& callback) const
{
    LOG_INFO << "updae " << s_document::key;

    Json::Value val{*req->jsonObject()};

    if (!(val.isMember("id") && val["id"].isInt()))
    {
        server::server::get().error_reply(callback);
        return;
    }

    s_document item{};
    item.read(val);

    if (val.isMember("body") && val["body"].isString())
    {
        auto result{nanodbc::execute(server::server::get().connection,
                                     "SELECT AccountId FROM Document "
                                     "WHERE Id = "
                                     + std::to_string(item.id))};
        if (!result.next())
        {
            server::server::get().error_reply(callback);
            return;
        }

        s_account acnt{};
        acnt.id = result.get<int>(0);

        using namespace drogon::utils;
        item.localPath = app().getUploadPath()
                + '/'
                + std::to_string(acnt.id)
                + '/'
                + document_item::categorie_name(item.category);
        std::filesystem::create_directories(item.localPath);

        std::ofstream file(item.get_path(),
                           std::ios::binary);
        if (!file.is_open())
        {
            server::server::get().error_reply(callback);
            return;
        }

        const auto decoded{base64Decode(val["body"].asString())};
        if (!file.write(decoded.data(), decoded.size()))
        {
            server::server::get().error_reply(callback);
            return;
        }
        file.close();

        item.state = document_item::Uploaded;

        server::server::get().update(req,
                                     callback,
                                     item,
                                     &acnt);
    }
    else
        server::server::get().update(req,
                                     callback,
                                     item);
}

void document_ctl::remove(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    LOG_INFO << "remove " << s_document::key;

    Json::Value val{*req->jsonObject()};

    if (!(val.isMember("id") && val["id"].isInt()))
    {
        server::server::get().error_reply(callback);
        return;
    }

    s_document item{};
    item.id = val["id"].asInt();

    auto result{nanodbc::execute(server::server::get().connection,
                                 "SELECT RelativePath, FileName, Extension FROM Document "
                                 "WHERE Id = "
                                 + to_string(item.id))};

    result.next();
    item.set(result);

    const auto path{item.get_path()};
    if (!path.empty()) filesystem::remove(path);

    server::server::get().remove(req,
                                 callback,
                                 item);
}
}
