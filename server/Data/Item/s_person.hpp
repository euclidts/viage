#ifndef S_PERSON_HPP
#define S_PERSON_HPP

#include <nanodbc/nanodbc.h>
#include <Item/person_item.hpp>

namespace Data
{
namespace People
{
struct s_person : virtual public person_item
{
    void read(const nanodbc::result& res);

protected:
    s_person();

    const std::string fields() const;
};

}
}

#endif // S_PERSON_HPP
