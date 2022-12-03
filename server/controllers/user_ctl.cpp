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

    while (users.next())
    {
        if (users.get<std::string>("Login") == userName)
        {
            std::cout << "password MD5 -- " << utils::getMd5(password)
                      << "\npassword in db -- " << utils::binaryStringToHex(reinterpret_cast<const unsigned char*>(users.get<std::string>("Password").c_str()), 16)
                      << "\n";

//            Json::Value ret;
//            ret["result"] = "ok";
//            ret["token"] = utils::getUuid();
//            auto resp{HttpResponse::newHttpJsonResponse(ret)};
//            callback(resp);
        }
    }
}
}
}
