#include <wobjectimpl.h>

#include "base_data.hpp"

W_OBJECT_IMPL(Data::base_data)

namespace Data
{
base_data::base_data(QObject* parent)
    : QObject{parent}
{}

bool base_data::getCompleted() const
{
    return completed;
}

void base_data::setCompleted(bool newCompleted)
{
    if (completed == newCompleted)
        return;
    completed = newCompleted;
    emit completedChanged();
}
}

