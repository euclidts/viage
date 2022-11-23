#pragma once

#include "wrapped_nested_list.hpp"
#include "qjsondocument.h"
#include <iostream>

namespace Wrapper
{
template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Interface::netManager* manager,
                                                       Data::c_list<Outer>* parentList,
                                                       QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{manager, context}
    , key{this->makeKey(parentList)}
    , parent_key_id{std::string{Outer{}.key()}.append("Id")}
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
    Json::Value val{Client::to_Json(obj)};

    json[QString::fromStdString(parent_key_id)] = id;
    QJsonDocument doc{json};
    QByteArray data{doc.toJson(QJsonDocument::Compact)};

    this->mng->postToKey(key.c_str(),
                         data,
                         [this, val](const Json::Value& res)
    {
        Json::Value concat{res};

        for (const auto member : val.getMemberNames())
            concat[member] = val[member];

        this->inner->appendWith(concat);
    },
    "addInWith error");
}

}
