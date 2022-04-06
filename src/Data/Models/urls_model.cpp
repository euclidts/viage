#include <wobjectimpl.h>

#include "urls_model.hpp"

namespace Data
{

W_OBJECT_IMPL(urls_model)

urls_model::urls_model(QObject* parent)
    : base_model<url_list, url_item>{parent}
{
}

}
