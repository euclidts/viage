#ifndef WRAPPED_LIST_HPP
#define WRAPPED_LIST_HPP

#include <QQmlContext>
#include <QJsonDocument>

#include <netManager.hpp>
#include <list.hpp>
#include <base_wrapper.hpp>

class Outer;

namespace Data
{
template <typename Outer>
class c_list;
}

namespace Wrapper
{

template <typename Inner>
class wrapped_list : public base_wrapper<Inner>
{
public:
    explicit wrapped_list()
        : base_wrapper<Inner>{}
    {}

    void makeConnections() const
    {
        this->connect(this->inner,
                      &Inner::validate,
                      this,
                      [this] (int id)
                      {
                          QJsonObject obj{};
                          auto item{this->inner->item_at_id(id)};
                          item.write(obj);

                          const auto key{this->inner->key()};

                          QJsonObject json{{ key, obj }};

                          Interface::netManager::instance().putToKey(key,
                              QJsonDocument{json}.toJson(),
                              [this] (const QJsonObject& rep)
                              {},
                              "Validate error");
                      });

        this->connect(this->inner,
                      &Inner::add,
                      this,
                      [this] ()
                      {
                          Interface::netManager::instance().postToKey(this->inner->key(),
                              QByteArray{},
                              [this](const QJsonObject& rep)
                              { this->inner->appendWith(rep); },
                              "Add error");
                      });

        this->connect(this->inner,
                      &Inner::addWith,
                      this,
                      [this] (const QJsonObject& obj)
                      {
                          Interface::netManager::instance().postToKey(this->inner->key(),
                              QJsonDocument{obj}.toJson(),
                              [this, obj] (const QJsonObject& res)
                              {
                                  auto map{res.toVariantMap()};
                                  map.insert(obj.toVariantMap());

                                  const auto json{QJsonObject::fromVariantMap(map)};
                                  this->inner->appendWith(json);
                              },
                              "addWith error");
                      });

        connectRemove();
    }

    void get() const
    {
        Interface::netManager::instance().getFromKey(this->inner->key(),
                                                     [this](const QByteArray& bytes)
                                                     { this->inner->read(bytes); });
    }

protected:
    void connectRemove() const
    {
        this->connect(this->inner,
                      &Inner::remove,
                      this,
                      [this] (int id)
                      {
                          this->inner->erase(id);
                          const QJsonObject json{{"id", id}};

                          Interface::netManager::instance().deleteToKey(this->inner->key(),
                              QJsonDocument{json}.toJson(),
                              [this, id](const QJsonObject&) {},
                              "Remove Error");
                      });
    }
};

}

#endif // WRAPPED_LIST_HPP
