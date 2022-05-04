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
                                                       QQmlContext* context)
    : wrapped_list<Inner>{srv, context}
{
}

template<typename Inner, typename Outer>
std::string wrapped_nested_item<Inner, Outer>::makeKey(item_list<Outer>* parentList)
{
    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(this->inner->key());

    return newkey;
}

template<typename Inner, typename Outer>
std::string wrapped_nested_item<Inner, Outer>::makeKey(item_list<Outer>* parentList, int id)
{
    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(std::to_string(id));
    newkey.append("/");
    newkey.append(this->inner->key());

    return newkey;
}

template<typename Inner, typename Outer>
void wrapped_nested_item<Inner, Outer>::makeConnections(item_list<Outer>* parentList)
{
    this->connect(this->inner,
                  &Inner::validate,
                  this,
                  [=] (int id)
    {
        Outer* outer = new Outer{parentList->item_at_id(id)};
        outer->set(this->inner);
        parentList->setItemAtId(id, *outer);

        this->service->putToKey(makeKey(parentList).c_str(),
                                this->inner->toData(id),
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

    this->connect(this->inner,
                  &Inner::loadFrom,
                  this,
                  [=] (int id)
    {
        this->service->getFromKey(makeKey(parentList, id).c_str(),
                                  [this](const QByteArray& rep)
        {
            if(rep.isEmpty())
                this->inner->clear();
            else
                this->inner->read(rep);
        });
    });

}

}
}
