#include <wobjectimpl.h>

#include "base_filter_model.hpp"

namespace Data {

W_OBJECT_IMPL(base_filter_model);

base_filter_model::base_filter_model(QAbstractItemModel *model, QObject* parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);

    setSourceModel(model);
    sort(0);
}

int base_filter_model::getSortIndex() const
{
    return sortIndex;
}

void base_filter_model::setSortIndex(int newSortIndex)
{
    if (sortIndex == newSortIndex)
        return;
    sortIndex = newSortIndex;
    sort(0);
}

}
