#include <wobjectimpl.h>

#include <Items/user_item.hpp>
#include "user_filter_model.hpp"

namespace Data
{
W_OBJECT_IMPL(user_filter_model)

user_filter_model::user_filter_model(QAbstractItemModel *model,
                                     const bool &exclusif,
                                     QObject *parent)
    : base_filter_model{model, parent}
    , isExclif{exclusif}
{
}

// Workarond to always emit filterRoleChanged
void user_filter_model::forceFilterRole(int role)
{
    if (filterRole() == role)
        emit this->filterRoleChanged(role);
    else
        this->setFilterRole(role);
}

bool user_filter_model::filterAcceptsRow(int sourceRow,
                                         const QModelIndex &sourceParent) const
{
    const auto& id{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    People::user_item::IdRole)};

    if (isExclif)
    {
        if (filterRole() == id)
            return true;
        else
            return false;
    }

    const auto& userName{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    People::user_item::LastNameRole)};

    const auto& company{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    People::user_item::CompanyRole)};

    if(userName.toString().contains(filterRegularExpression())
            || company.toString().contains(filterRegularExpression()))
        return true;

    return false;
}

bool user_filter_model::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    if (sortRole() == 0)
    {
        const auto leftData{sourceModel()->data(left, People::user_item::LastNameRole)};
        const auto rightData{sourceModel()->data(right, People::user_item::LastNameRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortRole() == 1)
    {
        const auto leftData{sourceModel()->data(left, People::user_item::CompanyRole)};
        const auto rightData{sourceModel()->data(right, People::user_item::CompanyRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortRole() == 2)
    {
        const auto leftData{sourceModel()->data(left, People::user_item::ClearanceRole)};
        const auto rightData{sourceModel()->data(right, People::user_item::ClearanceRole)};

        return leftData.toString() > rightData.toString();
    }

    return false;
}

}
