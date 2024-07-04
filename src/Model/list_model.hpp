#ifndef LIST_MODEL_HPP
#define LIST_MODEL_HPP

#include <QAbstractListModel>

#include <wobjectdefs.h>

namespace Data
{
template <typename T>
class list;

template <typename T>
class list_model : public QAbstractListModel
{
    W_OBJECT(list_model)

public:
    explicit list_model(QObject* parent = nullptr)
        : QAbstractListModel{parent}
    {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        if (parent.isValid() || !m_list)
            return 0;

        return m_list->size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid() || !m_list)
            return QVariant{};

        const T item = m_list->items().at(index.row());
        return item.data(role);
    }

    bool setData(const QModelIndex& index,
                 const QVariant& value,
                 int role = Qt::EditRole) override
    {
        if (!m_list)
            return false;

        T item = m_list->items().at(index.row());
        item.setData(value, role);

        if (m_list->setItemAt(index.row(), item))
        {
            emit this->dataChanged(index, index, QVector<int>() << role);
            return true;
        }
        return false;
    }

    Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
    }

    QHash<int, QByteArray> roleNames() const override { return T::roleNames(); }

    list<T>* getList() const { return m_list; }

    void setList(list<T>* newList)
    {
        beginResetModel();

        if (m_list) m_list->disconnect(this);

        m_list = newList;

        if (m_list)
        {
            connect(m_list, &list<T>::preItemsAppended,
                    this, [this](int number)
                    {
                        const int index = m_list->size();
                        beginInsertRows(QModelIndex(), index, index + number - 1);
                    });

            connect(m_list, &list<T>::postItemsAppended,
                    this, [this]()
                    { endInsertRows(); });

            connect(m_list, &list<T>::preItemsRemoved,
                    this, [this](int first, int last)
                    { beginRemoveRows(QModelIndex(), first, last); });

            connect(m_list, &list<T>::postItemsRemoved,
                    this, [this]()
                    { endRemoveRows(); });

            connect(m_list, &list<T>::dataChangedAt,
                    this, [this](int row)
                    { emit dataChanged(index(row), index(row)); });
        }

        endResetModel();
    }

    W_PROPERTY(list<T>*, list READ getList WRITE setList)

protected:
    list<T>* m_list{nullptr};
};

} // Data

#include <wobjectimpl.h>

W_OBJECT_IMPL(Data::list_model<T>, template <typename T>)

#endif // LIST_MODEL_HPP
