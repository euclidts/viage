#ifndef WRAPPED_CALCULATOR_HPP
#define WRAPPED_CALCULATOR_HPP

#include <base_wrapper.hpp>
#include <Lists/simple_item_list.hpp>
#include <Items/senior_citizen_item.hpp>
#include "life_expectency.hpp"

namespace Data
{
class rent_item;
}

namespace Calculator
{
using namespace Wrapper;

class wrapped_calculator final
        : public base_wrapper<simple_item_list<senior_citizen_item>>
{
public:
    wrapped_calculator(Interface::netManager* manager,
                       QQmlContext* context,
                       const QString& tempPath);

private:
    life_expectency exp;
    rent_item* rent;
    QString docxPath{};

    void calculate_rent();
    void write_to_file();
};
}

#endif // WRAPPED_CALCULATOR_HPP
