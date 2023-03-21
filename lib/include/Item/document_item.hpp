#ifndef DOCUMENT_ITEM_HPP
#define DOCUMENT_ITEM_HPP

#include <filesystem>
#include <json/json.h>
#include <base_data.hpp>
#include "item_list.hpp"

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

    static const constexpr char* categorie_name(categories c) noexcept
    {
        switch (c) {
        case None:
            return "None";
        case Picture:
            return "Picture";
        case Passeport:
            return "Passeport";
        case RegisteryExcerpt:
            return "RegisteryExcerpt";
        case PursuitExcerpt:
            return "PursuitExcerpt";
        case TaxDeclaration:
            return "TaxDeclaration";
        case BuildingDetails:
            return "BuildingDetails";
        case Insurance:
            return "Insurance";
        case Discernement:
            return "Discernement";
        case Beb:
            return "Beb";
        case Jobs:
            return "Jobs";
        case FutureJobs:
            return "FutureJobs";
        case Calculation:
            return "Calculation";
        case Other:
            return "Other";
        case Maintenance:
            return "Maintenance";
        case Constitution:
            return "Constitution";
        case PPE:
            return "PPE";
        case PPEPVS:
            return "PPEPVS";
        }
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

    template <typename T = document_item>
    static bool documents_completed(const std::vector<T>& docs, bool ppe)
    {
        bool uploaded{true};
        int flags{document_item::None};

        for (const auto& doc : docs)
        {
            if (doc.state != document_item::Uploaded)
            {
                uploaded = false;
                break;
            }

            flags |= doc.category;
        }

        if (uploaded)
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
        else
            return false;
    };

protected:
    explicit document_item();

    void set_file_info();
};
}

#endif // DOCUMENT_ITEM_HPP
