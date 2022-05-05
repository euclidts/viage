#include <wobjectimpl.h>

#include "rent_item.hpp"

namespace Data
{
W_OBJECT_IMPL(rent_item)

rent_item::rent_item(QObject *parent)
    : base_item{parent}
{
}

void rent_item::clear()
{
    expectency = 0;
    emit expectencyChanged();
}

double rent_item::getExpectency() const
{
    return expectency;
}

void rent_item::setExpectency(double newExpectency)
{
    if (qFuzzyCompare(expectency, newExpectency))
        return;
    expectency = newExpectency;
    emit expectencyChanged();
}

}
