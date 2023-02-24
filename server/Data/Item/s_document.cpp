#include "s_document.hpp"

namespace Data
{
s_document::s_document()
    : document_item{}
{
}

void s_document::set(const nanodbc::result& res)
{
    try
    {
        if (!res.is_null("Id"))
            id = res.get<int>("Id");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Category"))
            category = categories(res.get<int>("Category"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Extension"))
            extension = res.get<std::string>("Extension");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("FileName"))
            fileName = res.get<std::string>("FileName");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("isUploaded"))
            state = res.get<int>("isUploaded") ? Uploaded : NotUploded;
    }
    catch (...) {}
}

const string s_document::insert(const People::s_user& usr, s_account* acnt) const
{
    std::string str{"INSERT INTO Document "
                    "(Category, AccountId) "
                    "OUTPUT inserted.id "
                    "VALUES("
                    + std::to_string(category) +
                ", "
                + std::to_string(acnt->id) +
                "); "};

    acnt->foreign_update(str, acnt);
    acnt->condition(str, usr, acnt);

    return str;}

const string s_document::update(const People::s_user& usr, s_account* acnt) const
{
    return "UPDATE Document SET "
            "Category = "
            + std::to_string(category) +
            " , Extension = '"
            + extension +
            "' , FileName = '"
            + fileName +
            "' , isUploaded = '"
            + std::to_string(state == Uploaded) +
            " WHERE Id = "
            + std::to_string(id);
}

void s_document::foreign_update(std::string& query, bool complete, s_account* acnt)
{
    std::string str{server::utils::update_flag(
                    account_item::DocumentsCompleted,
                    "State",
                    complete)};
    acnt->foreign_update(str, complete, acnt);
    query.append(str);
}

void s_document::condition(std::string &query, const People::s_user &usr, s_account *acnt)
{
    acnt->condition(query, usr, acnt);
}

void s_document::update_reply(nanodbc::result& res, Value& json, s_account *acnt)
{
    acnt->update_reply(res, json);
}

}
