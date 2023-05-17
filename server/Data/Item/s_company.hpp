#ifndef S_COMPANY_HPP
#define S_COMPANY_HPP

#include <s_user.hpp>
#include <Item/company_item.hpp>

namespace Data
{
struct s_company final : public company_item
                       , public s_base_data
{
    explicit s_company();

    void set(const Row& row) override;
    void set(const Result& res) { s_base_data::set(res); };

    const std::string insert(const People::s_user& usr) const;
    const std::string select(const People::s_user& usr) const;
    const std::string update(const People::s_user& usr) const;

    static void foreign_update(std::string& query, bool complete) {};
    static void condition(std::string& query, const People::s_user& usr) {};
    static void select_updated(std::string& query) {};
    static void update_reply(const Result& res, Json::Value& json) {};

    static const constexpr std::string search(const People::s_user& usr)
    {
        if (usr.clearance < People::s_user::Administrator)
            return "";

        return "SELECT * "
               "FROM Company ";
    }
};

}

#endif // S_COMPANY_HPP
