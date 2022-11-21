#pragma once
#include <QQmlContext>

#include "qjsondocument.h"
#include "wrapped_list.hpp"

#include <netManager.hpp>
#include <item_list.hpp>
#include <client.hpp>

using namespace Client;

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
    { this->inner->read(to_Json(bytes)); });
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

        this->mng->putToKey(this->inner->key(),
                            to_QByteArray(json),
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
                  [this] (const QJsonObject& obj)
    {
        QJsonDocument doc{obj};
        QByteArray data{doc.toJson()};

        Json::Value val;
        Json::Reader reader;
        reader.parse(data.toStdString(), val);

        this->mng->postToKey(this->inner->key(),
                             data,
                             [this, val](const Json::Value& res)
        {
            Json::Value concat{val};
            concat[val.size()] = res;
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

        this->mng->deleteToKey(this->inner->key(),
                               to_QByteArray(json),
                               [this, id](const Json::Value& rep) {},
        "Remove Error");
    });
}
}
