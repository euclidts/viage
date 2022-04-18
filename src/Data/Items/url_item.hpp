#ifndef URL_ITEM_HPP
#define URL_ITEM_HPP

#include <QJsonObject>

namespace Data
{
struct url_item
{
    url_item(const QUrl address = QUrl{""});

    QUrl url;
    int id{0};

    enum roles
    {
        UrlRole = Qt::UserRole,
        IdRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonValue& json);
    const QJsonValue write() const;
};

}

#endif // URL_ITEM_HPP
