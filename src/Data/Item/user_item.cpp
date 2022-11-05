#include "user_item.hpp"

namespace Data
{
namespace People
{
user_item::user_item()
    : person_item()
    , address_item()
{
}

QHash<int, QByteArray> user_item::roleNames()
{
    QHash<int, QByteArray> names = person_item::roleNames();

    names[CompanyRole] = "company";
    names[ClearanceRole] = "clearance";
    names[TeamNameRole] = "team";
    names[BeneficiaryRole] = "beneficiary";

    names.insert(address_item::roleNames());

    names[IbanRole] = "iban";
    names[BicRole] = "bic";
    names[CompanyIdRole] = "companyId";
    names[TeamIdRole] = "teamId";
    names[LockedRole] = "isLocked";
    names[CompletedRole] = "completed";

    return names;
}

QVariant user_item::data(int role) const
{
    QVariant extra_data{person_item::data(role)};

    if (extra_data != QVariant())
        return extra_data;

    switch (role)
    {
    case CompanyRole:
        return QVariant(company);
    case ClearanceRole:
        return QVariant(clearance);
    case TeamNameRole:
        return QVariant(team);
    case BeneficiaryRole:
        return QVariant(beneficiary);
    case IbanRole:
        return QVariant(iban);
    case BicRole:
        return QVariant(bic);
    case CompanyIdRole:
        return QVariant(company_id);
    case TeamIdRole:
        return QVariant(team_id);
    case LockedRole:
        return QVariant(isLocked);
    case CompletedRole:
        return QVariant(is_completed());
}

    extra_data = address_item::data(role);

    if (extra_data != QVariant())
        return extra_data;

    return QVariant();
}

void user_item::setData(const QVariant &value, int role)
{
    person_item::setData(value, role);

    switch (role)
    {
    case CompanyRole:
        company = value.toString();
        break;
    case ClearanceRole:
        clearance = clearances(value.toInt());
        break;
    case TeamNameRole:
        team = value.toString();
        break;
    case BeneficiaryRole:
        beneficiary = value.toString();
        break;
    case IbanRole:
        iban = value.toString();
        break;
    case BicRole:
        bic = value.toString();
        break;
    case CompanyIdRole:
        company_id = value.toInt();
        break;
    case TeamIdRole:
        team_id = value.toInt();
        break;
    case LockedRole:
        isLocked = value.toBool();
        break;
    }

    address_item::setData(value, role);
}

void user_item::read(const QJsonObject &json)
{
    person_item::read(json);

    if (json.contains("company") && json["company"].isString())
        company = json["company"].toString();

    if (json.contains("clearance") && json["clearance"].isDouble())
        clearance = clearances(json["clearance"].toInt());

    if (json.contains("team") && json["team"].isString())
        team = json["team"].toString();

    if (json.contains("beneficiary") && json["beneficiary"].isString())
        beneficiary = json["beneficiary"].toString();

    if (json.contains("address") && json["address"].isObject())
        address_item::read(json["address"].toObject());

    if (json.contains("iban") && json["iban"].isString())
        iban = json["iban"].toString();

    if (json.contains("bic") && json["bic"].isString())
        bic = json["bic"].toString();

    if (json.contains("companyId") && json["companyId"].isDouble())
        company_id = json["companyId"].toInt();

    if (json.contains("teamId") && json["teamId"].isDouble())
        team_id = json["teamId"].toInt();

    if (json.contains("isLocked") && json["isLocked"].isBool())
        isLocked = json["isLocked"].toBool();
}

void user_item::write(QJsonObject& json) const
{
    person_item::write(json);

    json["company"] = company;
    json["clearance"] = clearance;
    json["team"] = team;
    json["beneficiary"] = beneficiary;

    QJsonObject jsonAddress{};
    address_item::write(jsonAddress);

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

    if(company == "")
        return false;

    if(team == "")
        return false;

    if(clearance == None)
        return false;

    if(beneficiary == "")
        return false;

    if(!address_item::is_completed())
        return false;

    if(iban == "")
        return false;

    if(bic == "")
        return false;

    return true;
}

}
}
