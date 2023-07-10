#include <drogon/HttpAppFramework.h>

#include "s_document.hpp"

namespace Data
{
s_document::s_document()
    : document_item{}
{
}

void s_document::set(const Row &row)
{
    try
    {
        if (!row["Id"].isNull())
            id = row["Id"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Category"].isNull())
            category = categories(row["Category"].as<int>());
    }
    catch (...) {}

    try
    {
        if (!row["Extension"].isNull())
            extension = row["Extension"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["FileName"].isNull())
            fileName = row["FileName"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["RelativePath"].isNull())
            localPath = row["RelativePath"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["isUploaded"].isNull())
            state = row["isUploaded"].as<bool>() ? Uploaded : NotUploded;
    }
    catch (...) {}
}

const std::string s_document::insert(const People::s_user& usr, const s_account* acnt) const
{
    std::string str{"INSERT INTO Document "
                    "(Category, AccountId) "
                    "VALUES("
                    + std::to_string(category) +
                ", "
                + std::to_string(acnt->id) +
                ") RETURNING Id"};

    acnt->foreign_update(str, acnt);

    return str;
}

const std::string s_document::select(const People::s_user& usr, const s_account* acnt) const
{
    return search(usr, acnt);
}

const std::string s_document::update(const People::s_user& usr,
                                     const s_account* acnt,
                                     const s_document* doc) const
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
                "' ";

    str += " WHERE Id = "
            + std::to_string(id);

    return str;
}

const std::string s_document::remove(const People::s_user& usr, const s_account* acnt) const
{
    return "DELETE FROM Document WHERE Id = " + std::to_string(id);
}

void s_document::foreign_update(std::string& query, bool complete,
                                const s_account* acnt,
                                const s_document* doc)
{
    if (acnt)
    {
        std::string str{};
        acnt->foreign_update(str, complete, acnt);
        query.append(str);
    }
}

void s_document::select_updated(std::string &query, const s_account* acnt, const s_document* doc)
{
    if (!acnt) return;
    acnt->select_updated(query, acnt);
}

void s_document::update_reply(const Result& res, Value& json,
                              const s_account* acnt,
                              const s_document* doc)
{
    acnt->update_reply(res, json);

    if (doc)
    {
        Value val;
        val["isUploaded"] = doc->state == Uploaded;
        json[key] = val;
    }
}

const std::filesystem::path s_document::get_directory(int acnt_id) const
{
    return drogon::app().getUploadPath()
            + '/'
            + std::to_string(acnt_id)
            + '/'
            + document_item::categorie_name(category);
}

void s_document::set_directory(int acnt_id)
{
    localPath = get_directory(acnt_id);
}

const std::filesystem::path s_document::get_path(int acnt_id) const
{
    if (fileName.empty() || extension.empty())
        return {};

    std::filesystem::path path{};

    if (!localPath.empty())
        path = localPath;
    else
    {
        if (acnt_id == 0) return {};
        else
            path = get_directory(acnt_id);
    }

    path.append(fileName + '.' + extension);
    return path;
}
}
