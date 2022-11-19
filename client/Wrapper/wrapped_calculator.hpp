#ifndef WRAPPED_CALCULATOR_HPP
#define WRAPPED_CALCULATOR_HPP

#include <duckx.hpp>

#include <base_wrapper.hpp>
#include <List/c_list.hpp>
#include <Item/c_senior_citizen.hpp>
#include "life_expectency.hpp"

namespace Data
{
class c_rent;
}

namespace Calculator
{
using namespace Wrapper;

class wrapped_calculator final
        : public base_wrapper<c_list<c_senior_citizen>>
{
public:
    wrapped_calculator(Interface::netManager* manager,
                       QQmlContext* context,
                       const QString& tempPath);

private:
    life_expectency exp;
    c_rent* rent;
    QString docxPath{};

    void calculate_rent();
    void write_to_file();

    void end_runs(duckx::Run& run);
    void skip_paragraphs(duckx::Paragraph& paragraphs, int n_skiped);
    void skip_runs(duckx::Run& runs, int n_skiped);
    void print_runs(duckx::Run& runs);
    void print_duckx();
};
}

#endif // WRAPPED_CALCULATOR_HPP
