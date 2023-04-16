#ifndef S_PERSON_HPP
#define S_PERSON_HPP

#include <Item/person_item.hpp>
#include <s_base_data.hpp>

namespace Data
{
namespace People
{
template <typename T>
struct s_person : virtual public person_item<T>
                , public s_base_data
{
    void set(const Row& row) override;

protected:
    s_person();

    const std::string fields() const override;
};

}
}

#include "s_person.cpp"
#endif // S_PERSON_HPP
