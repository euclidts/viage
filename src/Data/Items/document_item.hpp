#ifndef DOCUMENT_ITEM_H
#define DOCUMENT_ITEM_H

#define CATEGOIES_SUMED 1023

#include <QJsonObject>
#include <QFile>

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
        Picture = 1,
        Passeport = 2,
        RegisteryExcerpt = 4,
        PursuitExcerpt = 8,
        TaxDeclaration = 16,
        BuildingDetails = 32,
        Insurance = 64,
        Beb = 128,
        Jobs = 256,
        FutureJobs = 512
    };

    categories category{categories::None};
    QUrl relativePath{};
    QString fileName{""};
    QString extension{""};
    bool isUploaded{false};
    QDate uploadDate{};
    int id{0};

    enum roles
    {
        CategoryRole = Qt::UserRole,
        RelativePathRole,
        FileNameRole,
        ExtensionRole,
        IsUploadedRole,
        UploadDateRole,
        IdRole
    };

    QFile file{};

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
