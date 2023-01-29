#ifndef S_BASE_DATA_HPP
#define S_BASE_DATA_HPP

#include <nanodbc/nanodbc.h>
#include <base_data.hpp>

namespace Data
{
template <typename T>
struct s_base_data : virtual public base_data<T>
{
    virtual void set(nanodbc::result& res) = 0;

protected:
    s_base_data() {};
};

}

#endif // S_BASE_DATA_HPP
