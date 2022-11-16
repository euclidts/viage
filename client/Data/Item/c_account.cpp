#include <Item/owner_item.hpp>
#include <Item/contact_item.hpp>
#include <Item/habitat_item.hpp>
#include <Item/exterior_item.hpp>
#include <Item/document_item.hpp>
#include <List/item_list.hpp>
#include "c_account.hpp"

namespace Data
{
c_account::c_account()
    : account_item{}
    , c_base_item{}
{
    created = to_date_time(QDateTime::currentDateTime());
    modified = to_date_time(QDateTime::currentDateTime());
}

QHash<int, QByteArray> c_account::roleNames()
{
    QHash<int, QByteArray> names;

    names[OwnersRole] = "owners";
    names[ContactsRole] = "contacts";
    names[HabitatRole] = "habitat";
    names[ExteriorRole] = "exterior";
    names[DocumentsRole] = "documents";
    names[StateRole] = "state";
    names[ReceivedRole] = "receivedDate";
    names[TransmitedRole] = "transmitedDate";
    names[ExpertizedRole] = "expertiedDate";
    names[DecidedRole] = "decidedDate";
    names[NotarizedRole] = "notarizedDate";
    names[PaidRole] = "paidDate";
    names[CreatedRole] = "created";
    names[ModifiedRole] = "modified";
    names[AdvisorFirstNameRole] = "advisorFirstName";
    names[AdvisorLastNameRole] = "advisorLastName";
    names[CompanyRole] = "company";
    names[AcronymRole] = "acronym";
    names[IdRole] = "id";

    return names;
}

QVariant c_account::data(int role) const
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
    case ReceivedRole:
        return QVariant(receivedDate);
    case TransmitedRole:
        return QVariant(transmitedDate);
    case ExpertizedRole:
        return QVariant(expertizedDate);
    case DecidedRole:
        return QVariant(decidedDate);
    case NotarizedRole:
        return QVariant(notarizedDate);
    case PaidRole:
        return QVariant(paidDate);
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

void c_account::setData(const QVariant &value, int role)
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
    }
}

bool c_account::update(item_list<People::owner_item>* ol)
{
    Json::Value arr{};
    ol->write(arr);
    if (owners == arr)
        return false;

    owners = arr;
    modified = QDateTime::currentDateTime();
    return true;
}

bool c_account::update(item_list<People::contact_item>* cl)
{
    Json::Value arr{};
    cl->write(arr);
    // exception for first updating empty contacts
    if (contacts.empty() && arr.empty())
        return true;
    else if (contacts == arr)
        return false;

    contacts = arr;
    modified = QDateTime::currentDateTime();
    return true;
}

bool c_account::update(Places::habitat_item* ht)
{
    Json::Value obj{};
    ht->write(obj);
    if (habitat == obj)
        return false;

    habitat = obj;
    modified = QDateTime::currentDateTime();
    return true;
}

bool c_account::update(Places::exterior_item* er)
{
    Json::Value obj{};
    er->write(obj);
    if (exterior == obj)
        return false;

    exterior = obj;
    modified = QDateTime::currentDateTime();
    return true;
}

bool c_account::update(item_list<document_item>* ds)
{
    Json::Value arr{};
    ds->write(arr);
    // exception

    documents = arr;
    modified = QDateTime::currentDateTime();
    return true;
}

Json::Value c_account::get(item_list<People::owner_item> *ol) const
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

Json::Value c_account::get(item_list<People::contact_item> *cl) const
{
    // TODO : differentiate between "unfetched" and empty contacts
    return contacts;
}

Json::Value c_account::get(Places::habitat_item* ht) const
{
    if (habitat.isMember("id"))
        return habitat;
    else
        return {};
}

Json::Value c_account::get(Places::exterior_item* er) const
{
    if (exterior.isMember("id"))
        return exterior;
    else
        return {};
}

Json::Value c_account::get(item_list<document_item>* ds) const
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

QDateTime c_account::to_QDateTime(const std::string& date, const QString& format) const
{
    return QDateTime::fromString(QString::fromStdString(date), format);
}

std::string c_account::to_date_time(const QDateTime& date, const QString& format) const
{
    return date.toString(format).toStdString();
}

QVariantList c_account::to_QVariantList(const Value &json) const
{

}

}
