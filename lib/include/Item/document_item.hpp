#ifndef DOCUMENT_ITEM_HPP
#define DOCUMENT_ITEM_HPP

#include <filesystem>
#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
#define CATEGOIES_SUMED 4095
#define PPE_CATEGOIES_SUMED 131071

struct document_item : virtual public base_data<document_item>
{
    static const constexpr auto key{"document"};

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
        Discernement = 128,
        Beb = 256,
        Jobs = 512,
        FutureJobs = 1024,
        Calculation = 2048,
        Other = 4096,
        Maintenance = 8192,
        Constitution = 16384,
        PPE = 32768,
        PPEPVS = 65536
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

    static bool required_flags(int flags, bool ppe = false);

protected:
    explicit document_item();

    void set_file_info();
};

}

#endif // DOCUMENT_ITEM_HPP
