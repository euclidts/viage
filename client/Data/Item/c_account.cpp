#include "qjsonarray.h"
#include "qjsonobject.h"

#include <c_list.hpp>
#include "Item/c_contact.hpp"
#include "Item/c_document.hpp"
#include "Item/c_exterior.hpp"
#include "Item/c_habitat.hpp"
#include "Item/c_owner.hpp"
#include "c_account.hpp"
#include <client_utils.hpp>

using namespace client_utils;

namespace Data
{
c_account::c_account()
    : account_item{}
{
    created = to_date_time(QDateTime::currentDateTime());
    modified = to_date_time(QDateTime::currentDateTime());
}

QHash<int, QByteArray> c_account::roleNames()
{
    QHash<int, QByteArray> names;

    names[OwnersRole] = "owners";
//    names[ContactsRole] = "contacts";
    names[HabitatRole] = "habitat";
//    names[ExteriorRole] = "exterior";
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
        return to_QJsonArray(owners);
//    case ContactsRole:
//        return to_QJson(contacts);
    case HabitatRole:
        return to_QJsonObject(habitat);
//    case ExteriorRole:
//        return to_QJson(exterior);
    case DocumentsRole:
        return to_QJsonArray(documents);
    case StateRole:
        return QVariant(state);
    case ReceivedRole:
        return to_QDate(receivedDate);
    case TransmitedRole:
        return to_QDate(transmitedDate);
    case ExpertizedRole:
        return to_QDate(expertizedDate);
    case DecidedRole:
        return to_QDate(decidedDate);
    case NotarizedRole:
        return to_QDate(notarizedDate);
    case PaidRole:
        return to_QDate(paidDate);
    case CreatedRole:
        return to_QDateTime(created);
    case ModifiedRole:
        return to_QDateTime(modified);
    case AdvisorFirstNameRole:
        return to_QString(advisorFirstName);
    case AdvisorLastNameRole:
        return to_QString(advisorLastName);
    case CompanyRole:
        return to_QString(company);
    case AcronymRole:
        return to_QString(acronym);
    case IdRole:
        return QVariant(id);
    }

    return QVariant();
}

void c_account::setData(const QVariant &value, int role)
{
//    switch (role)
//    {
//    case OwnersRole:
//        owners = value.toJsonArray();
//        break;
//    case ContactsRole:
//        contacts = value.toJsonArray();
//        break;
//    case HabitatRole:
//        habitat = value.toJsonObject();
//        break;
//    case ExteriorRole:
//        exterior = value.toJsonObject();
//        break;
//    case DocumentsRole:
//        documents = value.toJsonArray();
//        break;
//    }
}

bool c_account::update(c_list<People::c_owner>* ol)
{
    Value arr{};
    ol->write(arr);
    if (owners == arr)
        return false;

    owners = arr;
    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(c_list<People::c_contact>* cl)
{
    Value arr{};
    cl->write(arr);
    // exception for first updating empty contacts
    if (contacts.empty() && arr.empty())
        return true;
    else if (contacts == arr)
        return false;

    contacts = arr;
    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(Places::c_habitat* ht)
{
    Value obj{};
    ht->write(obj);
    if (habitat == obj)
        return false;

    habitat = obj;
    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(Places::c_exterior* er)
{
    Value obj{};
    er->write(obj);
    if (exterior == obj)
        return false;

    exterior = obj;
    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(c_list<c_document>* ds)
{
    Value arr{};
    ds->write(arr);
    // exception

    documents = arr;
    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

Value c_account::get(c_list<People::c_owner> *ol) const
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

Value c_account::get(c_list<People::c_contact> *cl) const
{
    // TODO : differentiate between "unfetched" and empty contacts
    return contacts;
}

Value c_account::get(Places::c_habitat *ht) const
{
    if (habitat.isMember("id"))
        return habitat;
    else
        return {};
}

Value c_account::get(Places::c_exterior *er) const
{
    if (exterior.isMember("id"))
        return exterior;
    else
        return {};
}

Value c_account::get(c_list<c_document> *ds) const
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

}
