#ifndef URL_MODEL_H
#define URL_MODEL_H

#include <wobjectdefs.h>

#include "base_model.hpp"

#include <Lists/url_list.hpp>
#include <Items/url_item.hpp>

namespace Data
{

struct urls_model : public base_model<url_list, url_item>
{
    explicit urls_model(QObject* parent = nullptr);
    W_OBJECT(urls_model)
};
}

#endif // URL_MODEL_H
