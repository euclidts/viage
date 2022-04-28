#pragma once
#include <wobjectimpl.h>

#include "base_model.hpp"

namespace Data
{
W_OBJECT_IMPL((base_model<L, I>), template <typename L, typename I>)

template <typename L, typename I>
base_model<L, I>::base_model(QObject *parent)
    : QAbstractListModel(parent)
    , m_list(nullptr)
{
}

template <typename L, typename I>
int base_model<L, I>::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !m_list)
        return 0;

    return m_list->items().size();
}

template <typename L, typename I>
QVariant base_model<L, I>::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !this->m_list)
        return QVariant();

    const I item = this->m_list->items().at(index.row());
    return item.data(role);
}

template <typename L, typename I>
bool base_model<L, I>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!this->m_list)
        return false;

    I item = this->m_list->items().at(index.row());
    item.setData(value, role);

    if (this->m_list->setItemAt(index.row(), item))
    {
        emit this->dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

template <typename L, typename I>
Qt::ItemFlags base_model<L, I>::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

template <typename L, typename I>
QHash<int, QByteArray> base_model<L, I>::roleNames() const
{
    return I::roleNames();
}

template <typename L, typename I>
void base_model<L, I>::setList(L* newList)
{
    beginResetModel();

    if (m_list)
        m_list->disconnect(this);

    m_list = newList;

    if (m_list)
    {
        connect(m_list, &L::preItemsAppended,
                this, [=](int number) {
            const int index = m_list->items().size();
            beginInsertRows(QModelIndex(), index, index + number - 1);
        });

        connect(m_list, &L::postItemsAppended,
                this, [=]() {
            endInsertRows();
        });

        connect(m_list, &L::preItemsRemoved,
                this, [=](int first, int last) {
            beginRemoveRows(QModelIndex(), first, last);
        });

        connect(m_list, &L::postItemsRemoved,
                this, [=]() {
            endRemoveRows();
        });

        connect(m_list, &L::dataChangedAt,
                this, [this](int row) {
            emit dataChanged(index(row), index(row));
        });
    }

    endResetModel();
}

template<typename L, typename I>
L* base_model<L, I>::list() const
{
    return m_list;
}

}
