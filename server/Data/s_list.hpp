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
//    void write(const nanodbc::result& res);
};

}

#include "s_list.cpp"
#endif // S_LIST_HPP
