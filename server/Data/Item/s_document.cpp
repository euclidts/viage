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
    std::string str{"UPDATE Document SET "
                    "Category = "
                    + std::to_string(category) +
                ", Extension = '"
                + extension +
                "', FileName = '"
                + fileName +
                "', IsUploaded = "
                + std::to_string(state == Uploaded)};

    if (!localPath.empty())
        str += ", RelativePath = '"
                + localPath.string() +
                "' OUTPUT inserted.IsUploaded";

    str += " WHERE Id = "
            + std::to_string(id);

    return str;
}

void s_document::foreign_update(std::string& query, bool complete, s_account* acnt)
{
    if (acnt)
    {
        std::string str{};
        acnt->foreign_update(str, complete, acnt);
        query.append(str);
    }
}

void s_document::condition(std::string &query, const People::s_user &usr, s_account *acnt)
{
    if (acnt) acnt->condition(query, usr, acnt);
}

void s_document::update_reply(nanodbc::result& res, Value& json, s_account *acnt)
{
    res.next();
    try
    {
        if (!res.is_null("IsUploaded"))
        {
            Value val;
            val["isUploaded"] = (bool)res.get<int>("IsUploaded");
            json[key] = val;
        }
    }
    catch (...) {}
}

}
