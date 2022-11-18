#pragma once
#include <QQmlContext>

#include "wrapped_list.hpp"

#include <netManager.hpp>
#include <List/item_list.hpp>

namespace Wrapper
{
template <typename Inner>
wrapped_list<Inner>::wrapped_list(Interface::netManager* manager,
                                  QQmlContext* context)
    : base_wrapper<Inner>{manager, context}
{
}

template<typename Inner>
void wrapped_list<Inner>::get() const
{
    this->mng->getFromKey(this->inner->key(),
                          [this](const QByteArray& bytes)
    { this->inner->read(bytes); });
}

template<typename Inner>
void wrapped_list<Inner>::makeConnections() const
{
    this->connect(this->inner,
                  &Inner::validate,
                  this,
                  [this] (int id)
    {
        Json::Value obj;
        auto item{this->inner->item_at_id(id)};
        item.write(obj);

        Json::Value json;
        json[item.key()] = obj;

        Json::StreamWriterBuilder builder;
        const std::string str = Json::writeString(builder, json);

        this->mng->putToKey(this->inner->key(),
                            QByteArray::fromStdString(str),
                            [this](const Json::Value& rep)
        {},
        "Validate error");
    });

    this->connect(this->inner,
                  &Inner::add,
                  this,
                  [this] ()
    {
        this->mng->postToKey(this->inner->key(),
                             QByteArray{},
                             [this](const Json::Value& rep)
        { this->inner->appendWith(rep); },
        "Add error");
    });

    this->connect(this->inner,
                  &Inner::addWith,
                  this,
                  [this] (const Json::Value& obj)
    {
        Json::StreamWriterBuilder builder;
        const std::string str = Json::writeString(builder, obj);

        this->mng->postToKey(this->inner->key(),
                             QByteArray::fromStdString(str),
                             [this, obj](const Json::Value& res)
        {
            Json::Value concat{obj};
            concat[obj.size()] = res;
            this->inner->appendWith(concat);
        },
        "addWith error");
    });

    connectRemove();
}

template<typename Inner>
void wrapped_list<Inner>::connectRemove() const
{
    this->connect(this->inner,
                  &Inner::remove,
                  this,
                  [this] (int id)
    {
        this->inner->erase(id);

        Json::Value json;
        json["id"] = id;

        Json::StreamWriterBuilder builder;
        const std::string str = Json::writeString(builder, json);

        this->mng->deleteToKey(this->inner->key(),
                               QByteArray::fromStdString(str),
                               [this, id](const Json::Value& rep) {},
        "Remove Error");
    });
}
}
