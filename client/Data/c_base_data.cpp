#include <wobjectimpl.h>

#include "c_base_data.hpp"
#include <utils.hpp>

namespace Data
{
W_OBJECT_IMPL(c_base_data)

c_base_data::c_base_data(QObject* parent)
    : QObject{parent}
    , base_data{}
{
}

const QByteArray c_base_data::toData(const char* parentKey, int parentId)
{
    std::string str{parentKey};
    str.append("Id");

    Json::Value data;
    data[str] = parentId;

    writeWithKey(data);

    return Utils::to_QByteArray(data);
}

const QByteArray c_base_data::toData(int parentId)
{
    Json::Value data;
    data["Id"] = parentId;

    writeWithKey(data);

    return Utils::to_QByteArray(data);
}

bool c_base_data::getCompleted() const
{
    return completed;
}

void c_base_data::setCompleted(bool newCompleted)
{
    if (completed == newCompleted)
        return;
    completed = newCompleted;
    emit completedChanged();
}

}
