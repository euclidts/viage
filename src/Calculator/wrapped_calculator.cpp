#include <QQmlEngine>

#include "wrapped_calculator.hpp"
#include <Items/rent_item.hpp>

namespace Calculator
{
wrapped_calculator::wrapped_calculator(Interface::netManager* manager,
                                       QQmlContext* context)
    : base_wrapper<simple_item_list<senior_citizen_item>>{manager, context}
    , exp{inner}
    , rent{new rent_item{}}
{
    inner->appendItems(); // at least one senior for the calculation

    this->connect(rent,
                  &rent_item::calculate,
                  this,
                  [this] ()
    {
        rent->from_expectency(exp.get_expectency(rent->getBirthDay()));
    });

    context->setContextProperty("rent", rent);
}

}
