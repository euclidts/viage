#include "base_data.hpp"

namespace Data
{
base_data::base_data()
{
}

void base_data::writeWithKey(Json::Value &json) const
{
    Json::Value obj;
    write(obj);

    json[key()] = obj;
}

}
