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
void s_list<T>::read(nanodbc::result &res)
{
    std::vector<T> vec{};

    while (res.next())
    {
        T item{};
        item.read(res);
        vec.push_back(item);
    }

    this->set_list(vec);
}

}
