#ifndef S_BASE_DATA_HPP
#define S_BASE_DATA_HPP

#include <nanodbc/nanodbc.h>

namespace Data
{
struct s_base_data
{
    virtual void set(const nanodbc::result& res) {};
    virtual void set_next(nanodbc::result& res)
    {
        if (res.next()) set(res);
    };

protected:
    s_base_data() {};

    virtual const std::string fields() const { return {}; };
};

}

#endif // S_BASE_DATA_HPP
