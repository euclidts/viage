#ifndef S_LIST_HPP
#define S_LIST_HPP

#include <nanodbc/nanodbc.h>

#include <item_list.hpp>

namespace Data
{
template <typename T>
struct s_list : public item_list<T>
{
    s_list();

    void read(nanodbc::result& res);
    static const constexpr auto select()
    {
        return T::select();
    }

    template <typename Parent>
    static const constexpr auto select(Parent p)
    {
        return T::select(p);
    }
};

}

#include "s_list.cpp"
#endif // S_LIST_HPP
