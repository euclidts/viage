#include <QQmlEngine>

#include <Items/rent_item.hpp>
#include "wrapped_calculator.hpp"

namespace Calculator
{
wrapped_calculator::wrapped_calculator(Service::access* srv,
                                       QQmlContext* context)
    : base_wrapper<simple_item_list<senior_citizen_item>>{srv, context}
    , exp{inner}
    , rent{new rent_item{}}
{
    inner->appendItems(); // at least one senior for the calculation

    this->connect(rent,
                  &rent_item::calculate,
                  this,
                  [this] ()
    {
        rent->setExpectency(exp.get_expectency());
    });

    context->setContextProperty("rent", rent);
}

}
