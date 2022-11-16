#ifndef DOCUMENT_FILTER_MODEL_H
#define DOCUMENT_FILTER_MODEL_H

#include <QSortFilterProxyModel>
#include <wobjectdefs.h>
#include <Item/c_document.hpp>

namespace Data {

class document_filter_model : public QSortFilterProxyModel
{
    W_OBJECT(document_filter_model)

public:
    explicit document_filter_model(QObject* parent = nullptr);

    c_document::categories getCategory() const;
    void setCategory(c_document::categories newCategory);

    W_PROPERTY(c_document::categories, category READ getCategory WRITE setCategory)

private:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;

    c_document::categories category{c_document::categories::None};
};
}

#endif // DOCUMENT_FILTER_MODEL_H
