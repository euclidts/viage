#ifndef S_LIST_HPP
#define S_LIST_HPP

#include "s_user.hpp"
#include <nanodbc/nanodbc.h>

#include <item_list.hpp>

namespace Data
{
template <typename T>
struct s_list final : public item_list<T>
{
    s_list();

    void set(nanodbc::result& res);

    template <typename ...Foreign>
    std::string update(const People::s_user& usr, Foreign*... f) const;

    template <typename ...Foreign>
    static void condition(std::string& query,
                          const People::s_user& usr,
                          Foreign*... f)
    {
        T::condition(query, usr, f...);
    };

    template <typename ...Foreign>
    static const constexpr auto select(const People::s_user& usr, Foreign*... f)
    {
        return T::select(usr, f...);
    }
};

}

#include "s_list.cpp"
#endif // S_LIST_HPP
