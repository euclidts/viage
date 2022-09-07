#include <iostream>

#include <QQmlEngine>
#include <QFile>
#include <QDesktopServices>

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
    , docxPath{tempPath}
{
    inner->appendItems(); // at least one senior for the calculation

    this->connect(rent,
                  &rent_item::calculate,
                  this,
                  &wrapped_calculator::calculate_rent);

    this->connect(rent,
                  &rent_item::writeToFile,
                  this,
                  &wrapped_calculator::write_to_file);

    context->setContextProperty("rent", rent);
}

void wrapped_calculator::calculate_rent()
{
    rent->from_expectency(exp.get_expectency(rent->getBirthDay()));
}

void wrapped_calculator::write_to_file()
{
    QString newPath{docxPath + "/calcul.docx"};

    QFile file{newPath};
    if (!file.exists())
    {
        file.setFileName(":/data/calcul.docx");

        if (!file.copy(newPath))
            mng->replyError("Calculation Document copy error", file.errorString());
        // report error throug the net manager as it is connected to the bridge

        file.setFileName(newPath);
    }

    file.setPermissions(QFileDevice::WriteOther);
    duckx::Document doc{newPath.toStdString()};
    doc.open();
    auto p = doc.paragraphs();

    using namespace std;
    string txt{};

    // skip to pargraphs of interests
    for(int i{0}; i < 8; i++)
        p.next();

    auto r = p.runs();

    string str{"Date estimée de la transaction : "};
    str.append(rent->getBirthDay()
               .toString("dd/MM/yyyy")
               .toStdString());

    r.set_text(str);

    p.next();

    int i{0};
    for (const auto item : inner->items())
    {
        r = p.runs();

        auto partner{inner->item_at(i)};
        char sex = partner.sex == senior_citizen_item::M ? 'M' : 'F';

        str = "Partenaire ";
        str.append(to_string(i + 1));
        str.append(" : Madame / Monsieur, Date de naissance : ");
        str += sex;
        str.append(" , ");
        str.append(partner.birthDay.toString("dd/MM/yyyy").toStdString());

        r.set_text(str);

        p.next();
        i++;
    }

    // skip second partner paragraph
    if (i == 1) p.next();
    // skip address paragraph
    p.next();
    r = p.runs();

    str = ("Valeur estimée du bien : ");
    str.append(to_string(rent->getEstimation()));
    str.append(" Source : …………………………….");

    r.set_text(str);

    p.next();
    r = p.runs();

    str = ("Droit d’habitation : ");
    str.append(to_string(rent->getDab()));

    r.set_text(str);

    p.next();
    r = p.runs();

    str = ("Bouquet : ");
    str.append(to_string(rent->getBou()));

    r.set_text(str);

    doc.save();
    file.setPermissions(QFileDevice::ReadOwner);
    if(!QDesktopServices::openUrl(newPath))
        mng->replyError("Calculation Document error", "QDesktopervices : could not open .docx file");
}

}
