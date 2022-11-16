#include <Item/owner_item.hpp>
#include <Item/contact_item.hpp>
#include <Item/habitat_item.hpp>
#include <Item/exterior_item.hpp>
#include <Item/document_item.hpp>
#include <List/item_list.hpp>
#include "c_account.hpp"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

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
        return to_QDate(created);
    case ModifiedRole:
        return to_QDate(modified);
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

bool c_account::update(item_list<People::owner_item>* ol)
{
    bool up{account_item::update(ol)};
    if (!up)
        return false;

    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(item_list<People::contact_item>* cl)
{
    bool up{account_item::update(cl)};
    if (contacts.empty())
        return true;
    else if (!up)
        return false;

    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(Places::habitat_item* ht)
{
    bool up{account_item::update(ht)};
    if (!up)
        return false;

    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(Places::exterior_item* er)
{
    bool up{account_item::update(er)};
    if (!up)
        return false;

    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

bool c_account::update(item_list<document_item>* ds)
{
    bool up{account_item::update(ds)};
    if (!up)
        return false;

    modified = to_date_time(QDateTime::currentDateTime());
    return true;
}

QDateTime c_account::to_QDateTime(const std::string& date, const QString& format) const
{
    return QDateTime::fromString(QString::fromStdString(date), format);
}

std::string c_account::to_date_time(const QDateTime& date, const QString& format) const
{
    return date.toString(format).toStdString();
}

}
