#ifndef WRAPPED_NESTED_ITEM_HPP
#define WRAPPED_NESTED_ITEM_HPP

#include "wrapped_list.hpp"

namespace Data
{
class data_notifyer;
}

namespace Wrapper
{
template <typename Inner, typename Outer>
class wrapped_nested_item : public wrapped_list<Inner>
{
public:
    explicit wrapped_nested_item()
        : wrapped_list<Inner>{}
    {}

    void makeConnections(Data::list<Outer>* parentList)
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

                              Interface::netManager::instance().putToKey(makeKey(parentList).c_str(),
                                  this->inner->toData(id),
                                  [=](const QJsonObject& rep)
                                  {
                                      QJsonObject json;
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
                          const auto json = outer.get(this->inner);

                          this->inner->clear(); // clean previous load

                          if (json.empty())
                          {
                              Interface::netManager::instance().getFromKey(makeKey(parentList, id).c_str(),
                                                                           [this](const QByteArray& rep)
                                                                           {
                                                                               if(!rep.isEmpty())
                                                                                   this->inner->read(rep);
                                                                           });
                          }
                          else
                              this->inner->read(json);
                      });
    }

protected:
    std::string makeKey(Data::list<Outer>* parentList)
    {
        std::string newkey = parentList->key();
        newkey.append("/");
        newkey.append(this->inner->key());

        return newkey;
    }
    std::string makeKey(Data::list<Outer>* parentList, int id)
    {
        std::string newkey = parentList->key();
        newkey.append("/");
        newkey.append(std::to_string(id));
        newkey.append("/");
        newkey.append(this->inner->key());

        return newkey;
    }
};

} // Wrapper

#endif // WRAPPED_NESTED_ITEM_HPP
