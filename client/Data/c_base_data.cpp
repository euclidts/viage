#include <wobjectimpl.h>

#include "c_base_data.hpp"

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
    data[str] =  parentId;

    writeWithKey(data);

    Json::StreamWriterBuilder builder;
    const std::string bytes{Json::writeString(builder, data)};
    return QByteArray::fromStdString(bytes);
}

const QByteArray c_base_data::toData(int parentId)
{
    Json::Value data;
    data["Id"] = parentId;

    writeWithKey(data);

    Json::StreamWriterBuilder builder;
    const std::string bytes{Json::writeString(builder, data)};
    return QByteArray::fromStdString(bytes);
}

void c_base_data::read(const QByteArray& bytes)
{
    Json::Value json;
    Json::Reader reader;
    reader.parse(bytes.toStdString(), json);
    base_data::read(json);
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
