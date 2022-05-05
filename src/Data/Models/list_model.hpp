#ifndef LIST_MODEL_H
#define LIST_MODEL_H

#include <wobjectdefs.h>

namespace Data
{
template <typename L, typename I>
class base_model;

template <typename T>
class simple_item_list;

template <typename T>
struct list_model : public base_model<simple_item_list<T>, T>
{
    explicit list_model(QObject *parent = nullptr);
    W_OBJECT(list_model)
};
}

#include "list_model.cpp"
#endif // LIST_MODEL_H
