#ifndef S_PERSON_HPP
#define S_PERSON_HPP

#include <Item/person_item.hpp>
#include <s_base_data.hpp>
#include <models/metadata.hpp>

namespace Data
{
namespace People
{
template <typename T>
struct s_person : virtual public person_item<T>
                , public s_base_data
{
    static const std::vector<drogon_model::MetaData> metaData_;

    static const constexpr bool hasPrimaryKey{true};
    static const constexpr std::string primaryKeyName{"Id"};
    using PrimaryKeyType = int8_t;
    const constexpr PrimaryKeyType& getPrimaryKey() const { return person_item<T>::id; };

    void set(const Row& row) override;

protected:
    s_person();

    const std::string fields() const override;
};

}
}

#include "s_person.cpp"
#endif // S_PERSON_HPP
