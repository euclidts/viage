#ifndef S_LIST_HPP
#define S_LIST_HPP

#include <s_user.hpp>
#include "s_base_data.hpp"
#include <item_list.hpp>

namespace Data
{
template <typename T>
struct s_list final : public item_list<T>
                    , public s_base_data
{
    s_list();

    void set(const Result& res) override;
    void set(const Row& row) override {};

    template <typename ...Foreign>
    std::string update(const People::s_user& usr, const Foreign*... f) const;

    template <typename ...Foreign>
    static void foreign_update(std::string& query,
                               bool complete,
                               const Foreign*... f)
    {
        T::foreign_update(query, complete, f...);
    };

    template <typename ...Foreign>
    static void condition(std::string& query,
                          const People::s_user& usr,
                          const Foreign*... f)
    {
        T::condition(query, usr, f...);
    };

    template <typename ...Foreign>
    static void update_reply(const Result& res,
                             Json::Value& json,
                             const Foreign*... f)
    {
        T::update_reply(res, json, f...);
    };

    template <typename ...Foreign>
    static const constexpr auto search(const People::s_user& usr, Foreign*... f)
    {
        return T::search(usr, f...);
    }
};

}

#include "s_list.cpp"
#endif // S_LIST_HPP
