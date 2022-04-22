#include <wobjectimpl.h>

#include <Items/account_item.hpp>
#include "account_filter_model.hpp"

namespace Data {

W_OBJECT_IMPL(account_filter_model);

account_filter_model::account_filter_model(QAbstractItemModel* model, QObject* parent)
    : base_filter_model{model, parent}
{
}

bool account_filter_model::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const auto& owners{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    account_item::OwnersRole).toJsonArray()};

    const auto& owner_1{owners[0].toObject()};
    const auto& owner_2{owners[1].toObject()};

    if (owner_1["lastName"].toString()
            .contains(filterRegularExpression())
            || owner_2["lastName"].toString()
            .contains(filterRegularExpression()))
        return true;

    const auto& habitat{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    account_item::HabitatRole).toJsonObject()};

    if (habitat["street"].toString()
            .contains(filterRegularExpression())
            || habitat["canton"].toString()
            .contains(filterRegularExpression())
            || habitat["zip"].toString()
            .contains(filterRegularExpression())
            || habitat["city"].toString()
            .contains(filterRegularExpression()))
        return true;

    const auto& userName{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    account_item::UserLastNameRole)};
    const auto& company{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    account_item::CompanyRole)};

    if (userName.toString().contains(filterRegularExpression())
            || company.toString().contains(filterRegularExpression()))
        return true;

    const auto& acronym{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    account_item::AcronymRole)};

    if (acronym.toString().contains(filterRegularExpression()))
        return true;

    return false;
}

bool account_filter_model::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (sortIndex == 0)
    {
        const auto leftData{sourceModel()->data(left, account_item::CreatedRole)};
        const auto rightData{sourceModel()->data(right, account_item::CreatedRole)};

        return leftData.toDate() < rightData.toDate();
    }

    if (sortIndex == 1)
    {
        const auto leftData{sourceModel()->data(left, account_item::ModifiedRole)};
        const auto rightData{sourceModel()->data(right, account_item::ModifiedRole)};

        return leftData.toDate() < rightData.toDate();
    }

    if (sortIndex == 2)
    {
        const auto leftData{sourceModel()->data(left, account_item::AcronymRole)};
        const auto rightData{sourceModel()->data(right, account_item::AcronymRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortIndex == 3)
    {
        const auto leftData{sourceModel()->data(left, account_item::OwnersRole)};
        const auto rightData{sourceModel()->data(right, account_item::OwnersRole)};

        return leftData.toJsonArray()[0].toObject()["lastName"].toString()
                < rightData.toJsonArray()[0].toObject()["lastName"].toString();
    }

    if (sortIndex == 4)
    {
        const auto leftData{sourceModel()->data(left, account_item::HabitatRole)};
        const auto rightData{sourceModel()->data(right, account_item::HabitatRole)};

        return leftData.toJsonObject()["zip"].toString()
                < rightData.toJsonObject()["zip"].toString();
    }

    if (sortIndex == 5)
    {
        const auto leftData{sourceModel()->data(left, account_item::HabitatRole)};
        const auto rightData{sourceModel()->data(right, account_item::HabitatRole)};

        return leftData.toJsonObject()["canton"].toString()
                < rightData.toJsonObject()["canton"].toString();
    }

    if (sortIndex == 6)
    {
        const auto leftData{sourceModel()->data(left, account_item::UserLastNameRole)};
        const auto rightData{sourceModel()->data(right, account_item::UserLastNameRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortIndex == 7)
    {
        const auto leftData{sourceModel()->data(left, account_item::CompanyRole)};
        const auto rightData{sourceModel()->data(right, account_item::CompanyRole)};

        return leftData.toString() < rightData.toString();
    }

    return false;
}

}
