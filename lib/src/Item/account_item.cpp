#include <Item/account_item.hpp>

namespace Data
{
account_item::account_item()
    : base_data()
{
}

void account_item::read(const Value& json)
{
    if (json.isMember("owners") && json["owners"].isArray())
        owners = json["owners"];

    if (json.isMember("contacts") && json["contacts"].isArray())
        contacts = json["contacts"];

    if (json.isMember("habitat") && json["habitat"].isObject())
        habitat = json["habitat"];

    if (json.isMember("isPPE") && json["isPPE"].isBool())
        ppe = json["isPPE"].asBool();

    if (json.isMember("exterior") && json["exterior"].isObject())
        exterior = json["exterior"];

    if (json.isMember("documents") && json["documents"].isArray())
        documents = json["documents"];

    if (json.isMember("created") && json["created"].isString())
        created = json["created"].asString();

    if (json.isMember("modified") && json["modified"].isString())
        modified = json["modified"].asString();

    if (json.isMember("acronym") && json["acronym"].isString())
        acronym = json["acronym"].asString();

    if (json.isMember("advisorFirstName") && json["advisorFirstName"].isString())
        advisorFirstName = json["advisorFirstName"].asString();

    if (json.isMember("advisorLastName") && json["advisorLastName"].isString())
        advisorLastName = json["advisorLastName"].asString();

    if (json.isMember("company") && json["company"].isString())
        company = json["company"].asString();

    if (json.isMember("id") && json["id"].isInt())
        id = json["id"].asInt();

    if (json.isMember("state") && json["state"].isInt())
        state = states(json["state"].asInt());

    if (json.isMember("accountState") && json["accountState"].isInt())
        state = states(json["accountState"].asInt());

    if (json.isMember("receivedDate") && json["receivedDate"].isString())
        receivedDate = json["receivedDate"].asString();

    if (json.isMember("transmitedDate") && json["transmitedDate"].isString())
        transmitedDate = json["transmitedDate"].asString();

    if (json.isMember("expertizedDate") && json["expertizedDate"].isString())
        expertizedDate = json["expertizedDate"].asString();

    if (json.isMember("decidedDate") && json["decidedDate"].isString())
        decidedDate = json["decidedDate"].asString();

    if (json.isMember("notarizedDate") && json["notarizedDate"].isString())
        notarizedDate = json["notarizedDate"].asString();

    if (json.isMember("paidDate") && json["paidDate"].isString())
        paidDate = json["paidDate"].asString();
}

void account_item::write(Value &json) const
{
    if (!owners.empty())
        json["owners"] = owners;

    if (!contacts.empty())
        json["contacts"] = contacts;

    if (!habitat.empty())
        json["habitat"] = habitat;

    json["isPPE"] = ppe;

    if (!exterior.empty())
        json["exterior"] = exterior;

    if (!documents.empty())
        json["documents"] = documents;

    json["state"] = state;

    if (receivedDate != "")
        json["receivedDate"] = receivedDate;

    if (transmitedDate != "")
        json["transmitedDate"] = transmitedDate;

    if (expertizedDate != "")
        json["expertizedDate"] = expertizedDate;

    if (decidedDate != "")
        json["decidedDate"] = decidedDate;

    if (notarizedDate != notarizedDate)
        json["notarizedDate"] = notarizedDate;

    if (paidDate != "")
        json["paidDateDate"] = paidDate;

    json["created"] = created;

    if (modified != "")
        json["modified"] = modified;

    if (advisorFirstName != "")
        json["advisorFirstName"] = advisorFirstName;

    if (advisorLastName != "")
        json["advisorLastName"] = advisorLastName;

    if (company != "")
        json["company"] = company;

    if (acronym != "")
        json["acronym"] = acronym;

    json["id"] = id;
}

bool account_item::is_completed() const
{
    return (state & Onboarded) == Onboarded;
}

void account_item::clear()
{
    owners.clear();
    contacts.clear();
    habitat.clear();
    ppe = false;
    exterior.clear();
    documents.clear();
    created = "";
    modified = "";
    acronym = "";
    advisorFirstName = "";
    advisorLastName = "";
    company = "";
    id = 0;
    state = Initialized;
    receivedDate = "";
    transmitedDate = "";
    expertizedDate = "";
    decidedDate = "";
    notarizedDate = "";
    paidDate = "";
}

}
