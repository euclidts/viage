#include <QJsonArray>

#include <wobjectimpl.h>

#include "url_list.hpp"

namespace Data
{
W_OBJECT_IMPL(url_list)

url_list::url_list(QObject* parent)
    : base_list<url_item>{parent}
{
}

std::vector<url_item> url_list::get_list() const
{
    return m_items;
}

QJsonArray url_list::arrayFromList() const
{
    QJsonArray arr{};

    for (const auto& url : m_items)
    {
        QJsonObject json{};
        url.write(json);
        arr.push_back(json);
    }

    return arr;
}

void url_list::setFromArray(const QJsonArray &array)
{
    std::vector<url_item> new_vec{};

    for (const auto& json : array)
        new_vec.push_back(url_item{json.toObject()});

    set_list(new_vec);
}

}
