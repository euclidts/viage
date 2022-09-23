#ifndef DOCUMENT_ITEM_H
#define DOCUMENT_ITEM_H

#define CATEGOIES_SUMED 2047

#include <QJsonObject>

namespace Data
{
struct document_item
{
    document_item();

    static const constexpr char* key() { return "document"; };
    static const constexpr auto qmlName{"Document"};
    static const constexpr auto uri{"Data"};

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
        Beb = 128,
        Jobs = 256,
        FutureJobs = 512,
        Calculation = 1024
    };

    categories category{categories::None};
    QUrl relativePath{};
    QUrl localPath{};
    QString fileName{""};
    QString extension{""};
    bool isUploaded{false};
    bool uploading{false};
    float uploadProgress{0.f};
    QDate uploadDate{};
    int id{0};

    enum roles
    {
        CategoryRole = Qt::UserRole,
        RelativePathRole,
        LocalPathRole,
        FileNameRole,
        ExtensionRole,
        IsUploadedRole,
        UploadingRole,
        UploadProgressRole,
        UploadDateRole,
        IdRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    bool is_completed() const;

private:
    void setFileInfo();
};

}

#endif // DOCUMENT_ITEM_H
