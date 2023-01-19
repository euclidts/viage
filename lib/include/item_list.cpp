#pragma once

#include "item_list.hpp"

namespace Data
{
template <typename T>
item_list<T>::item_list()
    : base_data<item_list<T>>{}
{
}

template<typename T>
int item_list<T>::size() const
{
    return m_items.size();
}

template<typename T>
void item_list<T>::set_list(const std::vector<T>& list)
{
    m_items = list;
}

template<typename T>
T item_list<T>::item_at_id(int id) const
{
    int index{index_at_id(id)};

    if (index != -1)
        return m_items[index];

    return {};
}

template <typename T>
void item_list<T>::read(const Json::Value& array)
{
    std::vector<T> vec{};

    for (const auto& json : array)
    {
        // d'ont insert null values like "empty" contacts
        if (json.empty()) break;

        T item{};
        item.read(json);
        vec.push_back(item);
    }

    this->set_list(vec);
}

template <typename T>
void item_list<T>::write(Json::Value& json) const
{
    for (const auto& item : m_items)
    {
        Json::Value obj;
        item.write(obj);
        json.append(obj);
    }
}

template<typename T>
void item_list<T>::writeWithKey(Json::Value& json) const
{
    Json::Value array;
    write(array);

    json[this->key] = array;
}

template<typename T>
bool item_list<T>::is_completed() const
{
    if (m_items.empty())
        return false;

    for (const auto& item : m_items)
        if (!item.is_completed())
            return false;

    return true;
}

template<typename T>
int item_list<T>::index_at_id(int id) const noexcept
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

}
