#pragma once
#include <wobjectimpl.h>

#include "cached_nested_list.hpp"
#include "cache.hpp"

namespace Data
{
namespace Cache
{
W_OBJECT_IMPL((cached_nested_list<Inner, Outer>), template <typename Inner, typename Outer>)

template <typename Inner, typename Outer>
cached_nested_list<Inner, Outer>::cached_nested_list(cache* storage,
                                                     Service::access* srv,
                                                     item_list<Outer>* parentList,
                                                     QQmlContext* context)
    : cached_nested_item<Inner, Outer>{storage,
                                       srv,
                                       parentList,
                                       context}
{
    this->connect(this->item,
                  &Inner::addIn,
                  this,
                  [=] (int index)
    {
        auto outer = parentList->item_at(index);
        QString str{outer.key()};
        str.append("Id");

        QJsonObject json{ { str, outer.id} };
        QJsonDocument data{json};

        this->service->postToKey(this->item->key(),
                                 data.toJson(),
                                 [this](const QByteArray& res)
        {
            bool ok;
            const auto id{res.toInt(&ok)};

            if (ok)
                this->item->appendWith(id);
            else
                qDebug() << res;
        });
    });
}

}
}
