#ifndef BASE_FILTER_MODEL_HPP
#define BASE_FILTER_MODEL_HPP

#include <QSortFilterProxyModel>

#include <wobjectdefs.h>

namespace Data {

class base_filter_model : public QSortFilterProxyModel
{
    W_OBJECT(base_filter_model)

protected:
    explicit base_filter_model(QAbstractItemModel* model, QObject* parent = nullptr);
};
}

#endif // BASE_FILTER_MODEL_HPP
