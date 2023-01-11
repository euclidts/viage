#ifndef USER_ITEM_HPP
#define USER_ITEM_HPP

#include "person_item.hpp"
#include "address_item.hpp"

namespace Data
{
namespace People
{
struct user_item : virtual public person_item<user_item>
{
    user_item();

    static const constexpr char* key() noexcept { return "user"; };

    enum clearances
    {
        None,
        Vendor,
        Manager,
        Director,
        Administrator
    };

    Places::address_item* address;
    std::string company{""};
    int company_id{0};
    clearances clearance{Vendor};
    std::string team{""};
    int team_id{0};
    std::string beneficiary{""};
    std::string iban{""};
    std::string bic{""};
    bool isLocked{false};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}
}

#endif // USER_ITEM_HPP
