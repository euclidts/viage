#pragma once
#include "s_list.hpp"

namespace Data
{
template <typename T>
s_list<T>::s_list()
    : item_list<T>{}
{
}

template<typename T>
void s_list<T>::set(nanodbc::result& res)
{
    std::vector<T> vec{};

    while (res.next())
    {
        T item{};
        item.set(res);
        vec.push_back(item);
    }

    this->set_list(vec);
}

template<typename T>
template<typename ...Foreign>
std::string s_list<T>::update(const People::s_user& usr, Foreign*... f) const
{
    std::string str{};

    for (const auto& item : item_list<T>::m_items)
        str += item.update(usr, f...);

    return str;
}

}
