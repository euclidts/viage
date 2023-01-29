#ifndef S_INFANT_HPP
#define S_INFANT_HPP

#include <nanodbc/nanodbc.h>
#include "s_person.hpp"
#include <Item/infant_item.hpp>

namespace Data
{
namespace People
{
template <typename T>
struct s_infant : virtual public infant_item<T>
                , public s_person<T>
{
    void set(const nanodbc::result& res);

protected:
    s_infant();

    const std::string fields() const;
};

}
}

#include "s_infant.cpp"
#endif // S_INFANT_HPP
