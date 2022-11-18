#pragma once

#include "wrapped_nested_list.hpp"

namespace Wrapper
{
template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Interface::netManager* manager,
                                                       Data::c_list<Outer>* parentList,
                                                       QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{manager, context}
    , key{this->makeKey(parentList)}
    , parent_key_id{std::string{Outer::key()}.append("Id")}
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
void wrapped_nested_list<Inner, Outer>::add_in_with(int id, const Json::Value& obj)
{
    auto json{obj};
    json[parent_key_id] = id;

    Json::StreamWriterBuilder builder;
    const std::string str = Json::writeString(builder, json);

    this->mng->postToKey(key.c_str(),
                         QByteArray::fromStdString(str),
                         [this, obj](const Json::Value& res)
    {
        Json::Value concat{obj};
        concat[obj.size()] = res;
        this->inner->appendWith(concat); },
    "addInWith error");
}

}
