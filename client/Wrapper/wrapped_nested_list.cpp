#pragma once

#include "wrapped_nested_list.hpp"

namespace Wrapper
{
template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Interface::netManager* manager,
                                                       Data::item_list<Outer>* parentList,
                                                       QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{manager, context}
    , key{this->makeKey(parentList)}
    , parent_key_id{QString(Outer::key()).append("Id")}
{
    this->inner->complitionChecks();

    this->makeConnections(parentList);
    this->connectRemove();

    this->connect(this->inner,
                  &Inner::addIn,
                  this,
                  [this] (int id)
    { add_in_with(id); });

    this->connect(this->inner,
                  &Inner::addInWith,
                  this,
                  &wrapped_nested_list::add_in_with);
}

template<typename Inner, typename Outer>
void wrapped_nested_list<Inner, Outer>::add_in_with(int id, const QJsonObject& obj)
{
    auto json{obj};
    json[parent_key_id] = id;
    QJsonDocument data{json};

    this->mng->postToKey(key.c_str(),
                         data.toJson(),
                         [this, obj](const QJsonObject& res)
    {
        auto map{res.toVariantMap()};
        map.insert(obj.toVariantMap());

        const auto json{QJsonObject::fromVariantMap(map)};
        this->inner->appendWith(json);
    },
    "addInWith error");
}

}
