#ifndef ACCOUNT_FILTER_MODEL_HPP
#define ACCOUNT_FILTER_MODEL_HPP

#include <wobjectdefs.h>

#include "base_filter_model.hpp"

namespace Data {

class account_filter_model : public base_filter_model
{
    W_OBJECT(account_filter_model)

public:
    explicit account_filter_model(QAbstractItemModel *model, QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

};
}

#endif // ACCOUNT_FILTER_MODEL_HPP
