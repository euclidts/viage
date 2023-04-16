#ifndef S_ADDRESS_HPP
#define S_ADDRESS_HPP

#include <s_base_data.hpp>

namespace Data
{
namespace Places
{
struct address_item;

struct s_address final : public s_base_data
{
    explicit s_address(address_item* ai);

    void set(const Row& row) override;
    const std::string fields() const override;

protected:
    address_item* address;
};

}
}

#endif // S_ADDRESS_HPP
