#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include <QAbstractListModel>

#include <wobjectdefs.h>

namespace Data
{

template <typename L, typename I>
class base_model : public QAbstractListModel
{
    W_OBJECT(base_model)

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    L* list() const;
    void setList(L* newList);

    W_PROPERTY(L*, list READ list WRITE setList)

protected:
    explicit base_model(QObject *parent = nullptr);

    L* m_list;
};
}

#include "base_model.cpp"
#endif // BASE_MODEL_H
