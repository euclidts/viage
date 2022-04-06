#include <wobjectimpl.h>

#include <Items/advisor_item.hpp>
#include "advisor_filter_model.hpp"

namespace Data {

W_OBJECT_IMPL(advisor_filter_model);

advisor_filter_model::advisor_filter_model(QAbstractItemModel* model, QObject* parent)
    : base_filter_model{model, parent}
{
}

bool advisor_filter_model::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const auto& advisorName{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    People::advisor_item::LastNameRole)};

    const auto& company{sourceModel()->data(
                    sourceModel()->index(sourceRow, 0, sourceParent),
                    People::advisor_item::CompanyRole)};

    if(advisorName.toString().contains(filterRegularExpression())
            || company.toString().contains(filterRegularExpression()))
        return true;

    return false;
}

bool advisor_filter_model::lessThan(const QModelIndex& left, const QModelIndex& right) const
{
    if (sortIndex == 0)
    {
        const auto leftData{sourceModel()->data(left, People::advisor_item::LastNameRole)};
        const auto rightData{sourceModel()->data(right, People::advisor_item::LastNameRole)};

        return leftData.toString() < rightData.toString();
    }

    if (sortIndex == 1)
    {
        const auto leftData{sourceModel()->data(left, People::advisor_item::CompanyRole)};
        const auto rightData{sourceModel()->data(right, People::advisor_item::CompanyRole)};

        return leftData.toString() < rightData.toString();
    }

    return false;
}

}
