#include <Item/senior_citizen_item.hpp>

namespace Data
{
namespace People
{
senior_citizen_item::senior_citizen_item()
    : base_data{}
{
}

bool senior_citizen_item::is_completed() const
{
    return birthDay != "";
}

}
}
