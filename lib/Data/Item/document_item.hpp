#ifndef DOCUMENT_ITEM_COPY_H
#define DOCUMENT_ITEM_COPY_H

#include <filesystem>
#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
#define CATEGOIES_SUMED 4095

struct document_item : virtual public base_data
{
    document_item();

    static const constexpr char* key() { return "document"; };

    enum categories
    {
        None = 0,
        Picture = 1,
        Passeport = 2,
        RegisteryExcerpt = 4,
        PursuitExcerpt = 8,
        TaxDeclaration = 16,
        BuildingDetails = 32,
        Insurance = 64,
        Lucidity = 128,
        Beb = 256,
        Jobs = 512,
        FutureJobs = 1024,
        Calculation = 2048
    };

    categories category{categories::None};
    std::filesystem::path localPath{};
    std::string fileName{""};
    std::string extension{""};

    enum states
    {
        NotUploded,
        Uploading,
        Uploaded
    };

    states state{NotUploded};
    float uploadProgress{0.f};
    std::string uploadDate{""};
    int id{0};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;

protected:
    void set_file_info();
};

}

#endif // DOCUMENT_ITEM_COPY_H
