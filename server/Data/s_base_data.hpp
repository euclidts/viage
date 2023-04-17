#ifndef S_BASE_DATA_HPP
#define S_BASE_DATA_HPP

#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>

namespace Data
{
using Result = drogon::orm::Result;
using Row = drogon::orm::Row;

struct s_base_data
{
    virtual void set(const Row& row) = 0;
    virtual void set(const Result& res)
    {
        if (!res.empty()) set(res.front());
    };

protected:
    s_base_data() {};

    virtual const std::string fields() const { return {}; };
};

}

#endif // S_BASE_DATA_HPP
