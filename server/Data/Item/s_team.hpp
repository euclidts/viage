#ifndef S_TEAM_HPP
#define S_TEAM_HPP

#include "s_user.hpp"
#include "s_company.hpp"
#include <Item/team_item.hpp>

namespace Data
{
struct s_team final : public team_item
                    , public s_base_data
{
    explicit s_team();

    static const constexpr auto table{"Team"};

    int company_id{0};

    void set(const Row& row) override;
    void set(const Result& res) { s_base_data::set(res); };

    void read(const Json::Value& json);

    const std::string insert(const People::s_user& usr, const s_company* foreign = nullptr) const;
    const std::string select(const People::s_user& usr, const s_company* foreign = nullptr) const;
    const std::string update(const People::s_user& usr, const s_company* foreign = nullptr) const;
    const std::string remove(const People::s_user& usr, const s_company* foreign = nullptr) const;

    static void foreign_update(std::string& query,
                               bool complete,
                               const s_company* foreign = nullptr) {};

    static void select_updated(std::string& query,
                               const s_company* foreign = nullptr) {};

    static void update_reply(const Result& res,
                             Json::Value& json,
                             const s_company* foreign = nullptr) {};

    static const constexpr std::string search(const People::s_user& usr,
                                              const s_company* foreign = nullptr)
    {
        if (usr.clearance < People::s_user::Administrator && !foreign)
            return "";

        return "SELECT * FROM Team "
               "WHERE "
                + std::string{foreign->foreign_key}
        + " = "
        + std::to_string(foreign->id);
    }
};

}

#endif // S_COMPANY_HPP
