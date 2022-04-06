#pragma once
#include <wobjectimpl.h>

#include "cached_nested_item.hpp"
#include "cache.hpp"

namespace Data
{
namespace Cache
{
W_OBJECT_IMPL((cached_nested_item<Inner, Outer>), template <typename Inner, typename Outer>)

template <typename Inner, typename Outer>
cached_nested_item<Inner, Outer>::cached_nested_item(cache* storage,
                                                     Service::access* srv,
                                                     item_list<Outer>* parentList,
                                                     QQmlContext* context)
    : cached_list<Inner>{srv}
{
    this->connect(this->item,
            &Inner::validate,
            this,
            [=] (int index)
    {
        Outer* outer = new Outer{parentList->item_at(index)};
        outer->set(this->item);
//        storage->update(parentList->key(), index, outer.get(this->list), this->list->key);
        parentList->setItemAt(index, *outer);

        this->service->putToKey(makeKey(parentList).c_str(),
                                this->item->toData(outer->id),
                                [=](const QByteArray& rep)
        {
            const auto json = QJsonDocument::fromJson(rep).object();
            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                {
                    outer->read(json);
                    parentList->setItemAt(index, *outer);
                }
                else
                    qDebug() << json["errorMessage"].toString();
            };

            delete outer;
        });
    });

    this->connect(this->item,
            &Inner::loadFrom,
            this,
            [=] (int index)
    {
//        this->list->read(parentList->item_at(index).get(this->list));

        this->service->getFromKey(makeKey(parentList, index).c_str(),
                [this](const QByteArray& rep)
        {
            qDebug() << rep;
            this->item->read(rep);
        });
    });

    if (context)
        this->registerToQml(context);
}

template<typename Inner, typename Outer>
std::string cached_nested_item<Inner, Outer>::makeKey(item_list<Outer>* parentList)
{
    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(this->item->key());

    return newkey;
}

template<typename Inner, typename Outer>
std::string cached_nested_item<Inner, Outer>::makeKey(item_list<Outer>* parentList, int index)
{
    const int id = parentList->item_at(index).id;

    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(std::to_string(id));
    newkey.append("/");
    newkey.append(this->item->key());

    return newkey;
}

}
}
