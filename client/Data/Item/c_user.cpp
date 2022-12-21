#include <QVariant>

#include "c_user.hpp"
#include <client.hpp>

using namespace Client;

namespace Data
{
namespace People
{
c_user::c_user()
    : user_item{}
    , c_person{}
    , ca{address}
{
}

QHash<int, QByteArray> c_user::roleNames()
{
    QHash<int, QByteArray> names = c_person::roleNames();

    names[CompanyRole] = "company";
    names[ClearanceRole] = "clearance";
    names[TeamNameRole] = "team";
    names[BeneficiaryRole] = "beneficiary";

    names.insert(Places::c_address::roleNames());

    names[IbanRole] = "iban";
    names[BicRole] = "bic";
    names[CompanyIdRole] = "companyId";
    names[TeamIdRole] = "teamId";
    names[LockedRole] = "isLocked";
    names[CompletedRole] = "completed";

    return names;
}

QVariant c_user::data(int role) const
{
    QVariant extra_data{c_person::data(role)};

    if (extra_data != QVariant())
        return extra_data;

    switch (role)
    {
    case CompanyRole:
        return QString::fromStdString(company);
    case ClearanceRole:
        return QVariant(clearance);
    case TeamNameRole:
        return QString::fromStdString(team);
    case BeneficiaryRole:
        return QString::fromStdString(beneficiary);
    case IbanRole:
        return QString::fromStdString(iban);
    case BicRole:
        return QString::fromStdString(bic);
    case CompanyIdRole:
        return QVariant(company_id);
    case TeamIdRole:
        return QVariant(team_id);
    case LockedRole:
        return QVariant(isLocked);
    case CompletedRole:
        return QVariant(is_completed());
    }

    extra_data = ca.data(role);

    if (extra_data != QVariant())
        return extra_data;

    return QVariant();
}

void c_user::setData(const QVariant &value, int role)
{
    c_person::setData(value, role);

    switch (role)
    {
    case CompanyRole:
        company = to_string(value);
        break;
    case ClearanceRole:
        clearance = clearances(value.toInt());
        break;
    case TeamNameRole:
        team = to_string(value);
        break;
    case BeneficiaryRole:
        beneficiary = to_string(value);
        break;
    case IbanRole:
        iban = to_string(value);
        break;
    case BicRole:
        bic = to_string(value);
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

    ca.setData(value, role);
}

}
}
