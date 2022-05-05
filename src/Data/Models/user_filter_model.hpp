#ifndef USER_FILTER_MODEL_HPP
#define USER_FILTER_MODEL_HPP

#include "base_filter_model.hpp"

namespace Data {

class user_filter_model : public base_filter_model
{
public:
    explicit user_filter_model(QAbstractItemModel* model, QObject* parent = nullptr);

private:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
};
}

#endif // USER_FILTER_MODEL_HPP
