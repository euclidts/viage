#ifndef C_LIST_HPP
#define C_LIST_HPP

#include <json/value.h>
#include <wobjectdefs.h>

#include "c_simple_list.hpp"

namespace Data
{
template <typename T>
class c_list final : public c_simple_list<T>
{
    W_OBJECT(c_list)

public:
    explicit c_list(QObject* parent = nullptr);

    bool setItemAtId(int id, const T& item);
    void set_list(const std::vector<T>& list);
    void clear() override;
    W_SLOT(clear)

    void add()
    W_SIGNAL(add)
    void addWith(const Json::Value& obj)
    W_SIGNAL(addWith, obj)
    void addIn(int parentId)
    W_SIGNAL(addIn, parentId)
    void addInWith(int parentId, const Json::Value& obj)
    W_SIGNAL(addInWith, parentId, obj)

    void remove(int id)
    W_SIGNAL(remove, id)

    void appendWith(int id);
    void appendWith(const Json::Value& json);
    W_SLOT(appendWith, (const Json::Value&))

    void erase(int id);

    void read(const Json::Value& json);
    void read(const QByteArray& bytes);

    void complitionChecks() const;

private:
    void checkCompleted() override;
};

}

#include "c_list.cpp"
#endif // ITEM_LIST_HPP
