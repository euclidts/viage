#include "user_ctl.hpp"
#include <server.hpp>

namespace Data
{
namespace People
{
void user_ctl::auth(const HttpRequestPtr &req,
                    std::function<void (const HttpResponsePtr &)> &&callback,
                    std::string &&userName,
                    const std::string &password)
{
    LOG_DEBUG << "User " << userName << " login";

    auto users{nanodbc::execute(server::server::get().connection,
                                "SELECT "
                                "Id, "
                                "FirstName, "
                                "LastName, "
                                "Login, "
                                "EMail, "
                                "Phone, "
                                "Clearance, "
                                "Beneficiary, "
                                "Bic, "
                                "Iban, "
                                "Street, "
                                "City, "
                                "Canton, "
                                "Zip, "
                                "CompanyId, "
                                "TeamId, "
                                "IsLocked, "
                                "Password "
                                "FROM [User]")};

    HttpResponsePtr resp;

    using namespace utils;

    while (users.next())
    {
        if (users.get<std::string>("Login") == userName)
        {
            const auto pwd{users.get<std::string>("Password")};

            if (binaryStringToHex(reinterpret_cast<const unsigned char*>(pwd.c_str()), pwd.length())
                    == getMd5(password))
            {
                const auto uuid{utils::getUuid()};

                Json::Value json;
                json["sessionId"] = uuid;
                json["id"] = users.get<int>("Id");
                json["clearance"] = users.get<std::string>("Clearance");

                resp = HttpResponse::newHttpJsonResponse(json);
                break;
            }
        }
    }

    if (!resp)
    {
        resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
    }

    callback(resp);
}
}
}
