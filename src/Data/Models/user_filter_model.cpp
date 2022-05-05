#include <Items/user_item.hpp>
#include "user_filter_model.hpp"

namespace Data {

user_filter_model::user_filter_model(QAbstractItemModel* model, QObject* parent)
    : base_filter_model{model, parent}
{
}

bool user_filter_model::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
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
    if (sortIndex == 0)
    {
        const auto leftData{sourceModel()->data(left, People::user_item::LastNameRole)};
        const auto rightData{sourceModel()->data(right, People::user_item::LastNameRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortIndex == 1)
    {
        const auto leftData{sourceModel()->data(left, People::user_item::CompanyRole)};
        const auto rightData{sourceModel()->data(right, People::user_item::CompanyRole)};

        return leftData.toString() < rightData.toString();
    }

    return false;
}

}
