#include <QVariant>

#include "url_item.hpp"

namespace Data
{
url_item::url_item(const QUrl address)
    : url{address}
{
}

QHash<int, QByteArray> url_item::roleNames()
{
    QHash<int, QByteArray> names;

    names[UrlRole] = "url";

    return names;
}

QVariant url_item::data(int role) const
{
    if (role == UrlRole)
        return QVariant(url);

    return QVariant();
}

void url_item::setData(const QVariant &value, int role)
{
    if (role == UrlRole)
        url = value.toUrl();
}

void url_item::read(const QJsonValue& json)
{
        url = json.toString();
}

const QJsonValue url_item::write() const
{
    return QJsonValue(url.toString());
}

}
