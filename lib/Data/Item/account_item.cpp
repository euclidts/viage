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

bool account_item::update(item_list<People::owner_item>* ol)
{
    Value arr{};
    ol->write(arr);
    if (owners == arr)
        return false;

    owners = arr;
    return true;
}

bool account_item::update(item_list<People::contact_item>* cl)
{
    Value arr{};
    cl->write(arr);
    // exception for first updating empty contacts
    if (contacts.empty() && arr.empty())
        return true;
    else if (contacts == arr)
        return false;

    contacts = arr;
    return true;
}

bool account_item::update(Places::habitat_item* ht)
{
    Value obj{};
    ht->write(obj);
    if (habitat == obj)
        return false;

    habitat = obj;
    return true;
}

bool account_item::update(Places::exterior_item* er)
{
    Value obj{};
    er->write(obj);
    if (exterior == obj)
        return false;

    exterior = obj;
    return true;
}

bool account_item::update(item_list<document_item>* ds)
{
    Value arr{};
    ds->write(arr);
    // exception

    documents = arr;
    return true;
}

Value account_item::get(item_list<People::owner_item> *ol) const
{
    if (owners.empty())
        return owners;
    else
    {
        if (owners[0].isMember("id"))
            return owners;
        else
            return {};
        // no need to retreive initial "names only" array
    }
}

Value account_item::get(item_list<People::contact_item> *cl) const
{
    // TODO : differentiate between "unfetched" and empty contacts
    return contacts;
}

Value account_item::get(Places::habitat_item* ht) const
{
    if (habitat.isMember("id"))
        return habitat;
    else
        return {};
}

Value account_item::get(Places::exterior_item* er) const
{
    if (exterior.isMember("id"))
        return exterior;
    else
        return {};
}

Value account_item::get(item_list<document_item>* ds) const
{
    if (documents.empty())
        return documents;
    else
    {
        if (documents[0].isMember("id"))
            return documents;
        else
            return {};
    }
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
