#include <wobjectimpl.h>

#include <Item/c_user.hpp>
#include "user_filter_model.hpp"

namespace Data
{
W_OBJECT_IMPL(user_filter_model)

user_filter_model::user_filter_model(QAbstractItemModel *model,
                                     bool exclusif,
                                     QObject *parent)
    : base_filter_model{model, parent}
    , isExclusif{exclusif}
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
                    People::c_user::IdRole)};

    if (isExclusif)
    {
        if (filterRole() == id)
            return true;
        else
            return false;
    }

    const auto& userName{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    People::c_user::LastNameRole)};

    const auto& company{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    People::c_user::CompanyRole)};

    if(userName.toString().contains(filterRegularExpression())
            || company.toString().contains(filterRegularExpression()))
        return true;

    return false;
}

bool user_filter_model::lessThan(const QModelIndex& left, const QModelIndex& right) const
{

    if (sortRole() == 0)
    {
        const auto leftData{sourceModel()->data(left, People::c_user::CompanyRole)};
        const auto rightData{sourceModel()->data(right, People::c_user::CompanyRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortRole() == 1)
    {
        const auto leftData{sourceModel()->data(left, People::c_user::LastNameRole)};
        const auto rightData{sourceModel()->data(right, People::c_user::LastNameRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortRole() == 2)
    {
        const auto leftData{sourceModel()->data(left, People::c_user::ClearanceRole)};
        const auto rightData{sourceModel()->data(right, People::c_user::ClearanceRole)};

        return leftData.toString() > rightData.toString();
    }

    return false;
}

}
