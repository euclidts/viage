#ifndef URL_LIST_HPP
#define URL_LIST_HPP

#include <wobjectdefs.h>

#include "base_list.hpp"
#include <Items/url_item.hpp>

namespace Data
{

struct url_list : public base_list<url_item>
{
    W_OBJECT(url_list)

public:
    explicit url_list(QObject* parent = nullptr);

    std::vector<url_item> get_list() const;

    QJsonArray arrayFromList() const;
    void setFromArray(const QJsonArray& array);

    bool empty() const { return m_items.empty(); }
    W_INVOKABLE(empty)
};

};

#endif // URL_LIST_HPP
