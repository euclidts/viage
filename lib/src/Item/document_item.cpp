#include <Item/document_item.hpp>

namespace Data
{
document_item::document_item()
{
}

void document_item::read(const Json::Value &json)
{    
    if (json.isMember("category") && json["category"].isInt())
        category = categories(json["category"].asInt());

    if (json.isMember("isUploaded") && json["isUploaded"].isBool())
        json["isUploaded"].asBool() ? state = Uploaded : state = NotUploded;

    if(state == Uploaded)
    {
        if (json.isMember("uploadDate") && json["uplaodDate"].isString())
            uploadDate = json["uploadDate"].asString();
    }

    bool name_and_extension{false};

    if (json.isMember("fileName") && json["fileName"].isString())
    {
        fileName = json["fileName"].asString();
        name_and_extension = true;
    }

    if (json.isMember("extension") && json["extension"].isString())
    {
        extension = json["extension"].asString();
        name_and_extension = name_and_extension && true;
    }

    if (json.isMember("localPath") && json["localPath"].isString())
    {
        localPath = json["localPath"].asString();

        if (!name_and_extension)
            set_file_info();
    }

    if (json.isMember("id") && json["id"].isInt())
        id = json["id"].asInt();
}

void document_item::write(Json::Value &json) const
{
    json["category"] = category;
    json["isUploaded"] = state == Uploaded;
    json["fileName"] = fileName;
    json["extension"] = extension;
    json["id"] = id;
}

bool document_item::is_completed() const
{
    if (fileName == "")
        return false;

    return state == Uploaded;
}

bool document_item::required_flags(int flags, bool ppe)
{
    bool res{flags & Picture
                && flags & Passeport
                && flags & RegisteryExcerpt
                && flags & PursuitExcerpt
                && flags & TaxDeclaration
                && flags & BuildingDetails
                && flags & Insurance
                && flags & Discernement
                && flags & Calculation};

    if (!res) return false;

    if (ppe)
        res = flags & Constitution
                && flags & PPE
                && flags & PPEPVS;

    return res;
}

void document_item::set_file_info()
{
    if (localPath.empty())
        return;

    std::string str{localPath.extension().string()};
    str.erase(0, 1);
    extension = str;
    fileName = localPath.stem().string();
}

}
