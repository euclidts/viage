#include <Item/owner_item.hpp>
#include <Item/contact_item.hpp>
#include <Item/habitat_item.hpp>
#include <Item/exterior_item.hpp>
#include <Item/document_item.hpp>

#include <List/item_list.hpp>

#include "account_item.hpp"

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
    json["owners"] = owners;
    json["contacts"] = contacts;
    json["habitat"] = habitat;
    json["exterior"] = exterior;
    json["documents"] = documents;
    json["state"] = state;
    json["receivedDate"] = receivedDate;
    json["transmitedDate"] = transmitedDate;
    json["expertizedDate"] = expertizedDate;
    json["decidedDate"] = decidedDate;
    json["notarizedDate"] = notarizedDate;
    json["paidDateDate"] = paidDate;
    json["created"] = created;
    json["modified"] = modified;
    json["advisorFirstName"] = advisorFirstName;
    json["advisorLastName"] = advisorLastName;
    json["company"] = company;
    json["acronym"] = acronym;
    json["id"] = id;
}

bool account_item::is_completed() const
{
    return (state & Onboarded) == Onboarded;
}

}
