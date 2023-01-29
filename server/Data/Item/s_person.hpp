#ifndef S_PERSON_HPP
#define S_PERSON_HPP

#include <nanodbc/nanodbc.h>
#include <Item/person_item.hpp>
//#include <s_base_data.hpp>

namespace Data
{
namespace People
{
template <typename T>
struct s_person : virtual public person_item<T>
//                , virtual public s_base_data<person_item<T>>
{
    void set(const nanodbc::result& res);

protected:
    s_person();

    const std::string fields() const;
};

}
}

#include "s_person.cpp"
#endif // S_PERSON_HPP
