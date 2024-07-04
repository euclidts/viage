#ifndef LIST_HPP
#define LIST_HPP

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <wobjectdefs.h>

#include "base_data.hpp"
#include "list.hpp"

namespace Data
{
template <typename T>
class list final : public base_data
{    
    W_OBJECT(list)

public:
    list(QObject* parent = nullptr)
        : base_data{parent}
    {
        std::string str{T::key()};

        if (str.back() == 'y')
        {
            str.pop_back();
            str += "ie";
        }

        str += 's';

        auto key_str = new char[str.length() + 1];
        strcpy(key_str, str.c_str());
        m_key = key_str;

        str = T::qmlName();
        str += "List";

        auto qml_str = new char[str.length() + 1];
        strcpy(qml_str, str.c_str());
        m_qmlName = qml_str;
    }

    const constexpr auto key() const noexcept { return m_key; }
    const constexpr auto qmlName() const noexcept { return m_qmlName; }
    static const constexpr auto uri() { return T::uri(); }

    QVector<T> items() const
    {
        return m_items;
    }
    T item_at(int index) const
    {
        return m_items[index];
    }
    T item_at_id(int id) const
    {
        int index{index_at_id(id)};

        if (index != -1)
            return m_items[index];

        return {};
    }

    bool setItemAt(int index, const T& item)
    {
        if (index < 0 || index >= size())
            return false;

        m_items[index] = item;

        emit dataChangedAt(index);

        return true;
    }

    void preItemsAppended(int number = 1)
    W_SIGNAL(preItemsAppended, number)
    void postItemsAppended()
    W_SIGNAL(postItemsAppended)

        void appendItems(int number = 1)
    {
        emit preItemsAppended(number);

        for (int i = 0; i < number; i++)
            m_items.push_back(T{});

        emit postItemsAppended();
    }
    W_SLOT(appendItems, (int))

    void preItemsRemoved(int first, int last)
    W_SIGNAL(preItemsRemoved, first, last)
    void postItemsRemoved()
    W_SIGNAL(postItemsRemoved)

    void dataChangedAt(int index)
    W_SIGNAL(dataChangedAt, index)

        void removeItems(int first, int last)
    {
        emit preItemsRemoved(first, last);

        m_items.erase(m_items.begin() + first,
                      std::next(m_items.begin() + last));

        emit postItemsRemoved();
    }
    W_SLOT(removeItems, (int, int))

    void removeItems(int number = 1)
    {
        const auto count = size();

        removeItems(count - number, count - 1);
    }
    W_SLOT(removeItems, (int))

    bool setItemAtId(int id, const T& item)
    {
        int index{index_at_id(id)};

        if (index == -1)
            return false;

        m_items[index] = item;
        emit dataChangedAt(index);
        return true;
    }
    void set_list(const QVector<T>& list)
    {
        clear();
        emit preItemsAppended(size());

        m_items = list;

        emit postItemsAppended();
    }
    void clear() override
    {
        emit preItemsRemoved(0, size() - 1);

        m_items.clear();

        emit postItemsRemoved();
    }
    W_INVOKABLE(clear)

    void add()
    W_SIGNAL(add)
    void addWith(const QJsonObject& obj)
    W_SIGNAL(addWith, obj)
    void addIn(int parentId)
    W_SIGNAL(addIn, parentId)
    void addInWith(int parentId, const QJsonObject& obj)
    W_SIGNAL(addInWith, parentId, obj)

    void remove(int id)
    W_SIGNAL(remove, id)

        void appendWith(int id)
    {
        emit preItemsAppended(1);

        T item{};
        item.id = id;
        m_items.push_back(item);

        emit postItemsAppended();
    }
    void appendWith(const QJsonObject& json)
    {
        emit preItemsAppended(1);

        T item{};
        item.read(json);
        m_items.push_back(item);

        emit postItemsAppended();
    }

    void erase(int id)
    {
        int index{index_at_id(id)};

        if (index == -1)
            return;

        emit preItemsRemoved(index, index);

        m_items.erase(m_items.begin() + index);

        emit postItemsRemoved();
    }

    void read(const QJsonArray& array)
    {
        clear();
        emit preItemsAppended(array.size());

        for (const auto& json : array)
        {
            // d'ont insert null values like "empty" contacts
            if (json.isNull()) break;

            T item{};
            item.read(json.toObject());
            m_items.push_back(item);
        }

        emit postItemsAppended();
        emit loaded();
    }
    void read(const QByteArray& bytes)
    {
        const auto json = QJsonDocument::fromJson(bytes).array();
        read(json);
    }
    void write(QJsonArray& json) const
    {
        for (const auto& item : m_items)
        {
            QJsonObject obj{};
            item.write(obj);
            json.push_back(obj);
        }
    }

    const QByteArray toData(const char* parentKey, int parentId)
    {
        QString str{parentKey};
        str.append("Id");

        QJsonObject data{ {str, parentId} };

        writeWithKey(data);

        QJsonDocument bytes{data};
        return bytes.toJson();
    }

    const QByteArray toData(int parentId)
    {
        QJsonObject data{ {"Id", parentId} };

        writeWithKey(data);

        QJsonDocument bytes{data};
        return bytes.toJson();
    }

    bool is_completed() const
    {
        if (m_items.empty())
            return false;

        for (const auto& item : m_items)
            if (!item.is_completed())
                return false;

        return true;
    }

    qsizetype size() const { return m_items.size(); }

    void complitionChecks() const
    {
        base_data::connect(this, &list::postItemsAppended,
                           this, &list::checkCompleted);

        base_data::connect(this, &list::postItemsRemoved,
                           this, &list::checkCompleted);

        base_data::connect(this, &list::dataChangedAt,
                           this, &list::checkCompleted);
    }
    bool is_empty_completed() const
    {
        if(m_items.empty())
            return true;

        for(const auto& item : m_items)
            if (!item.is_completed())
                return false;

        return true;
    }

private:
    const char* m_key;
    const char* m_qmlName;

    void checkCompleted()
    {
        setCompleted(is_completed());
    }
    int index_at_id(int id) const noexcept
    {
        int index{-1};

        for (int i = 0; i < m_items.size(); i++)
            if (m_items[i].id == id)
            {
                index = i;
                break;
            }

        return index;
    }

    void writeWithKey(QJsonObject& json) const
    {
        QJsonArray array{};
        write(array);

        json[key()] = array;
    }

    QVector<T> m_items;
};

} // Data

#include <wobjectimpl.h>

W_OBJECT_IMPL(Data::list<T>, template <typename T>)

#endif // LIST_HPP
