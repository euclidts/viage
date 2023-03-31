#include <Item/user_item.hpp>

namespace Data
{
namespace People
{
user_item::user_item()
    : person_item()
    , address{new Places::address_item{}}
{
}

void user_item::read(const Json::Value &json)
{
    person_item::read(json);

    if (json.isMember("company") && json["company"].isString())
        company = json["company"].asString();

    if (json.isMember("clearance") && json["clearance"].isInt())
        clearance = clearances(json["clearance"].asInt());

    if (json.isMember("team") && json["team"].isString())
        team = json["team"].asString();

    if (json.isMember("beneficiary") && json["beneficiary"].isString())
        beneficiary = json["beneficiary"].asString();

    if (json.isMember("address") && json["address"].isObject())
        address->read(json["address"]);

    if (json.isMember("iban") && json["iban"].isString())
        iban = json["iban"].asString();

    if (json.isMember("bic") && json["bic"].isString())
        bic = json["bic"].asString();

    if (json.isMember("companyId") && json["companyId"].isInt())
        company_id = json["companyId"].asInt();

    if (json.isMember("teamId") && json["teamId"].isInt())
        team_id = json["teamId"].asInt();

    if (json.isMember("isLocked") && json["isLocked"].isBool())
        isLocked = json["isLocked"].asBool();
}

void user_item::write(Json::Value &json) const
{
    person_item::write(json);

    json["company"] = company;
    json["clearance"] = clearance;
    json["team"] = team;
    json["beneficiary"] = beneficiary;

    Json::Value jsonAddress;
    address->write(jsonAddress);

    json["address"] = jsonAddress;
    json["iban"] = iban;
    json["bic"] = bic;
    json["companyId"] = company_id;
    json["teamId"] = team_id;
    json["isLocked"] = isLocked;
}

bool user_item::is_completed() const
{
    if(!person_item::is_completed())
        return  false;

    if(eMail == "")
        return  false;

    if(company == "")
        return false;

    if(team == "")
        return false;

    if(clearance == None)
        return false;

    if(beneficiary == "")
        return false;

    if(!address->is_completed())
        return false;

    if(iban == "")
        return false;

    if(bic == "")
        return false;

    return true;
}

}
}
