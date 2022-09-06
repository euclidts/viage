#include <iostream>

#include <QQmlEngine>
#include <QFile>

#include <duckx.hpp>

#include "wrapped_calculator.hpp"
#include <Items/rent_item.hpp>

namespace Calculator
{
wrapped_calculator::wrapped_calculator(Interface::netManager* manager,
                                       QQmlContext* context,
                                       const QString& tempPath)
    : base_wrapper<simple_item_list<senior_citizen_item>>{manager, context}
    , exp{inner}
    , rent{new rent_item{}}
{
    inner->appendItems(); // at least one senior for the calculation

    this->connect(rent,
                  &rent_item::calculate,
                  this,
                  &wrapped_calculator::calculate_rent);

    context->setContextProperty("rent", rent);

    QFile file{":/data/calcul.docx"};
    file.copy(tempPath + "/calcul.docx");

    duckx::Document doc{QString{tempPath + "/calcul.docx"}.toStdString()};

    doc.open();

    for (auto p = doc.paragraphs(); p.has_next(); p.next())
    {
        for (auto r = p.runs(); r.has_next(); r.next())
        {
            std::cout << r.get_text() << std::endl;
        }
    }
}

void wrapped_calculator::calculate_rent()
{
    rent->from_expectency(exp.get_expectency(rent->getBirthDay()));
}

void wrapped_calculator::writeToFile(QString &path)
{
    duckx::Document doc{":/data/calcul.docx"};

    doc.open();

    for (auto p : doc.paragraphs())
        for (auto r : p.runs())
            std::cout << r.get_text() << std::endl;
}

}
