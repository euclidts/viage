#ifndef ADVISOR_FILTER_MODEL_HPP
#define ADVISOR_FILTER_MODEL_HPP

#include <wobjectdefs.h>

#include "base_filter_model.hpp"

namespace Data {

class advisor_filter_model : public base_filter_model
{
    W_OBJECT(advisor_filter_model)

public:
    explicit advisor_filter_model(QAbstractItemModel* model, QObject* parent = nullptr);

private:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
};
}

#endif // ACCOUNT_FILTER_MODEL_HPP
