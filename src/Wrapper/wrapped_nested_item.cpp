#pragma once
#include <wobjectimpl.h>

#include "wrapped_nested_item.hpp"

namespace Data
{
namespace Wrapper
{
W_OBJECT_IMPL((wrapped_nested_item<Inner, Outer>), template <typename Inner, typename Outer>)

template <typename Inner, typename Outer>
wrapped_nested_item<Inner, Outer>::wrapped_nested_item(Service::access* srv,
                                                     item_list<Outer>* parentList,
                                                     QQmlContext* context)
    : wrapped_list<Inner>{srv}
{
    this->connect(this->item,
            &Inner::validate,
            this,
            [=] (int id)
    {
        Outer* outer = new Outer{parentList->item_at_id(id)};
        outer->set(this->item);
        parentList->setItemAtId(id, *outer);

        this->service->putToKey(makeKey(parentList).c_str(),
                                this->item->toData(id),
                                [=](const QByteArray& rep)
        {
            const auto json = QJsonDocument::fromJson(rep).object();
            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                {
                    outer->read(json);
                    parentList->setItemAtId(id, *outer);
                }
                else
                    qDebug() << "validate error :" << json["errorMessage"].toString();
            };

            delete outer;
        });
    });

    this->connect(this->item,
            &Inner::loadFrom,
            this,
            [=] (int id)
    {
        this->service->getFromKey(makeKey(parentList, id).c_str(),
                [this](const QByteArray& rep)
        { this->item->read(rep); });
    });

    if (context)
        this->registerToQml(context);
}

template<typename Inner, typename Outer>
std::string wrapped_nested_item<Inner, Outer>::makeKey(item_list<Outer>* parentList)
{
    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(this->item->key());

    return newkey;
}

template<typename Inner, typename Outer>
std::string wrapped_nested_item<Inner, Outer>::makeKey(item_list<Outer>* parentList, int id)
{
    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(std::to_string(id));
    newkey.append("/");
    newkey.append(this->item->key());

    return newkey;
}

}
}
