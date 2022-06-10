#include <QJsonDocument>

#include "Items/owner_item.hpp"
#include "Items/contact_item.hpp"
#include "Items/habitat_item.hpp"
#include "Items/exterior_item.hpp"
#include "Items/document_item.hpp"

#include "Lists/item_list.hpp"

#include "account_item.hpp"

namespace Data
{
account_item::account_item()
    : created{QDateTime::currentDateTime()}
    , modified{QDateTime::currentDateTime()}
{
}

QHash<int, QByteArray> account_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[OwnersRole] = "owners";
    names[ContactsRole] = "contacts";
    // --- Habitat ---
    names[HabitatRole] = "habitat";
    // --- Exterior ---
    names[ExteriorRole] = "exterior";
    // --- Documents ---
    names[DocumentsRole] = "documents";
    // Account status
    names[StateRole] = "state";
    names[CreatedRole] = "created";
    names[ModifiedRole] = "modified";
    names[AdvisorFirstNameRole] = "advisorFirstName";
    names[AdvisorLastNameRole] = "advisorLastName";
    names[CompanyRole] = "company";
    names[AcronymRole] = "acronym";
    names[IdRole] = "id";

    return names;
}

QVariant account_item::data(int role) const
{
    switch (role)
    {
    case OwnersRole:
        return owners.toVariantList();
    case ContactsRole:
        return contacts.toVariantList();
    case HabitatRole:
        return habitat;
    case ExteriorRole:
        return exterior;
    case DocumentsRole:
        return documents.toVariantList();
    case StateRole:
        return QVariant(state);
    case CreatedRole:
        return QVariant(created);
    case ModifiedRole:
        return QVariant(modified);
    case AdvisorFirstNameRole:
        return QVariant(advisorFirstName);
    case AdvisorLastNameRole:
        return QVariant(advisorLastName);
    case CompanyRole:
        return QVariant(company);
    case AcronymRole:
        return QVariant(acronym);
    case IdRole:
        return QVariant(id);
    }

    return QVariant();
}

void account_item::setData(const QVariant &value, int role)
{
    switch (role)
    {
    case OwnersRole:
        owners = value.toJsonArray();
        break;
    case ContactsRole:
        contacts = value.toJsonArray();
        break;
    case HabitatRole:
        habitat = value.toJsonObject();
        break;
    case ExteriorRole:
        exterior = value.toJsonObject();
        break;
    case DocumentsRole:
        documents = value.toJsonArray();
        break;
    case StateRole:
        state = states(value.toInt());
        break;
    }
}

void account_item::set(item_list<People::owner_item>* ol)
{
    QJsonArray arr{};
    ol->write(arr);
    owners = arr;

    modified = QDateTime::currentDateTime();
}

void account_item::set(item_list<People::contact_item>* cl)
{
    QJsonArray arr{};
    cl->write(arr);
    contacts = arr;

    modified = QDateTime::currentDateTime();
}

void account_item::set(Places::habitat_item* ht)
{
    QJsonObject obj{};
    ht->write(obj);
    habitat = obj;

    modified = QDateTime::currentDateTime();
}

void account_item::set(Places::exterior_item* er)
{
    QJsonObject obj{};
    er->write(obj);
    exterior = obj;

    modified = QDateTime::currentDateTime();
}

void account_item::set(item_list<document_item>* ds)
{
    QJsonArray arr{};
    ds->write(arr);
    documents = arr;

    modified = QDateTime::currentDateTime();
}

QJsonArray account_item::get(item_list<People::owner_item> *ol)
{
    if (owners.isEmpty())
    {
        item_list<People::owner_item> newOwners{};
        newOwners.appendItems(); // at least one owner

        QJsonArray arr{};
        newOwners.write(arr);
        owners = arr;
    }

    return owners;
}

QJsonArray account_item::get(item_list<People::contact_item> *cl) const
{
    return contacts;
}

QJsonObject account_item::get(Places::habitat_item* ht)
{
    if (habitat.isEmpty())
    {
        QJsonObject obj{};

        Places::habitat_item newHabitat{};
        newHabitat.write(obj);
        habitat = obj;
    }

    return habitat;
}

QJsonObject account_item::get(Places::exterior_item* er)
{
    if (exterior.isEmpty())
    {
        QJsonObject obj{};

        Places::exterior_item newExterior{};
        newExterior.write(obj);
        exterior = obj;
    }

    return exterior;
}

QJsonArray account_item::get(item_list<document_item>* ds) const
{
    return documents;
}

void account_item::read(const QJsonObject& json)
{
    if (json.contains("owners") && json["owners"].isArray())
        owners = json["owners"].toArray();

    if (json.contains("contacts") && json["contacts"].isArray())
        contacts = json["contacts"].toArray();

    if (json.contains("habitat") && json["habitat"].isObject())
        habitat = json["habitat"].toObject();

    if (json.contains("exterior") && json["exterior"].isObject())
        exterior = json["exterior"].toObject();

    if (json.contains("documents") && json["documents"].isArray())
        documents = json["documents"].toArray();

    if (json.contains("created") && json["created"].isString())
        created = QDateTime::fromString(json["created"].toString(), "dd.MM.yyyy");


    if (json.contains("modified") && json["modified"].isString())
        modified = QDateTime::fromString(json["modified"].toString(), "dd.MM.yyyy");

    if (json.contains("acronym") && json["acronym"].isString())
        acronym = json["acronym"].toString();

    if (json.contains("advisorFirstName") && json["advisorFirstName"].isString())
        advisorFirstName = json["advisorFirstName"].toString();

    if (json.contains("advisorLastName") && json["advisorLastName"].isString())
        advisorLastName = json["advisorLastName"].toString();

    if (json.contains("company") && json["company"].isString())
        company = json["company"].toString();

    if (json.contains("id") && json["id"].isDouble())
        id = json["id"].toInt();

    if (json.contains("state") && json["state"].isDouble())
        state = states(json["state"].toInt());

    if (json.contains("accountState") && json["accountState"].isDouble())
        state = states(json["accountState"].toInt());
}

void account_item::write(QJsonObject& json) const
{
    json["owners"] = owners;
    json["contacts"] = contacts;
    json["habitat"] = habitat;
    json["exterior"] = exterior;
    json["documents"] = documents;
    json["state"] = state;
    json["created"] = created.toString("dd.MM.yyyy");
    json["modified"] = modified.toString("dd.MM.yyyy");
    json["advisorFirstName"] = advisorFirstName;
    json["advisorLastName"] = advisorLastName;
    json["company"] = company;
    json["acronym"] = acronym;
    json["id"] = id;
}

bool account_item::is_completed() const
{
    if (state > 16)
        return true;

    return false;
}

}
