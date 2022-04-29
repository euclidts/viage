#ifndef DOCUMENT_ITEM_H
#define DOCUMENT_ITEM_H

#include <QJsonObject>

namespace Data
{
struct document_item
{
    document_item();

    const constexpr char* key() { return "document"; };
    static const constexpr auto qmlName{"Document"};
    static const constexpr auto uri{"Data"};

    enum categories
    {
        None = 0,
        Picture,
        Passeport,
        RegisteryExcerpt,
        PursuitExcerpt,
        TaxDeclaration,
        BuildingDetails,
        Insurance,
        Beb,
        Jobs,
        FutureJobs
    };

    categories category{categories::None};
    bool isUploaded{false};
    QUrl url{};
    int id{0};

    enum roles
    {
        Category = Qt::UserRole,
        IsUploaded,
        UrlRole,
        IdRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
};

}

#endif // DOCUMENT_ITEM_H
