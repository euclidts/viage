#pragma once
#include <wobjectimpl.h>

#include "wrapped_nested_list.hpp"

namespace Data
{
namespace Wrapper
{
W_OBJECT_IMPL((wrapped_nested_list<Inner, Outer>), template <typename Inner, typename Outer>)

template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Service::access* srv,
                                                     item_list<Outer>* parentList,
                                                     QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{srv,
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

        QJsonObject json{ {str, outer.id} };
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
