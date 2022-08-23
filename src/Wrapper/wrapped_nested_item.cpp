#pragma once

#include "wrapped_nested_item.hpp"

namespace Wrapper
{
template <typename Inner, typename Outer>
wrapped_nested_item<Inner, Outer>::wrapped_nested_item(Interface::netManager* manager,
                                                       QQmlContext* context)
    : wrapped_list<Inner>{manager, context}
{
}

template<typename Inner, typename Outer>
std::string wrapped_nested_item<Inner, Outer>::makeKey(Data::item_list<Outer>* parentList)
{
    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(this->inner->key());

    return newkey;
}

template<typename Inner, typename Outer>
std::string wrapped_nested_item<Inner, Outer>::makeKey(Data::item_list<Outer>* parentList, int id)
{
    std::string newkey = parentList->key();
    newkey.append("/");
    newkey.append(std::to_string(id));
    newkey.append("/");
    newkey.append(this->inner->key());

    return newkey;
}

template<typename Inner, typename Outer>
void wrapped_nested_item<Inner, Outer>::makeConnections(Data::item_list<Outer>* parentList)
{
    this->connect(this->inner,
                  &Inner::validate,
                  this,
                  [this, parentList] (int id)
    {
        Outer outer{parentList->item_at_id(id)};

        if (outer.update(this->inner))
        {
            parentList->setItemAtId(id, outer);

            this->mng->putToKey(makeKey(parentList).c_str(),
                                this->inner->toData(id),
                                [=](const QJsonObject& rep)
            {
                QJsonObject json{};
                Outer updated{};
                outer.write(json);
                updated.read(json);
                updated.read(rep);
                parentList->setItemAtId(id, updated);
            },
            "Validate error");
        }
    });

    this->connect(this->inner,
                  &Inner::loadFrom,
                  this,
                  [this, parentList] (int id)
    {
        Outer outer{parentList->item_at_id(id)};
        auto json{outer.get(this->inner)};

        if (json.isEmpty())
        {
            this->mng->getFromKey(makeKey(parentList, id).c_str(),
                                  [this](const QByteArray& rep)
            {
                if(rep.isEmpty())
                    this->inner->clear();
                else
                    this->inner->read(rep);
            });
        }
        else
            this->inner->read(json);
    });

}

}
