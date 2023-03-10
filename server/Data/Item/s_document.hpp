#ifndef S_DOCUMENT_HPP
#define S_DOCUMENT_HPP

#include "s_account.hpp"
#include <server_utils.hpp>
#include <Item/document_item.hpp>

namespace Data
{
struct s_document final : public document_item
                        , public s_base_data
{
    s_document();

    void set(const nanodbc::result& res) override;

    const std::string insert(const People::s_user& usr, s_account* acnt = nullptr) const;
    const std::string update(const People::s_user& usr, s_account* acnt = nullptr) const;
    const std::string remove(const People::s_user& usr, s_account* acnt = nullptr) const;

    static void foreign_update(std::string& query,
                               bool complete,
                               s_account* acnt = nullptr);

    static void condition(std::string& query,
                          const People::s_user& usr,
                          s_account* acnt = nullptr);

    static void update_reply(nanodbc::result& res,
                             Json::Value& json,
                             s_account* acnt = nullptr);

    static const constexpr std::string select(const People::s_user& usr,
                                              s_account* acnt)
    {
        return "SELECT DISTINCT "
               "d.Id, "
               "Category, "
               "Extension, "
               "FileName, "
               "isUploaded "
               "FROM Account a, "
               "Document d, "
               "[User] u "
               "WHERE d.AccountId = "
                + std::to_string(acnt->id) +
                " "
                + server::utils::clearance_close(usr);
    }

    const filesystem::path get_path() const;
};
}

#endif // s_document_HPP
