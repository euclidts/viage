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
    names[TeamNumberRole] = "team";
    names[BeneficiaryRole] = "beneficiary";

    names.insert(address_item::roleNames());

    names[IbanRole] = "iban";
    names[BicRole] = "bic";

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
    case TeamNumberRole:
        return QVariant(team);
    case BeneficiaryRole:
        return QVariant(beneficiary);
    case IbanRole:
        return QVariant(iban);
    case BicRole:
        return QVariant(bic);
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
        clearance = value.toInt();
        break;
    case TeamNumberRole:
        team = value.toInt();
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
    }

    address_item::setData(value, role);
}

void user_item::read(const QJsonObject &json)
{
    person_item::read(json);

    if (json.contains("company") && json["company"].isString())
        company = json["company"].toString();

    if (json.contains("clearance") && json["clearance"].isDouble())
        clearance = json["clearance"].toInt();

    if (json.contains("team") && json["team"].isDouble())
        team = json["team"].toInt();

    if (json.contains("beneficiary") && json["beneficiary"].isString())
        beneficiary = json["beneficiary"].toString();

    if (json.contains("address") && json["address"].isObject())
        address_item::read(json["address"].toObject());

    if (json.contains("iban") && json["iban"].isString())
        iban = json["iban"].toString();

    if (json.contains("bic") && json["bic"].isString())
        bic = json["bic"].toString();
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
}

}
}
