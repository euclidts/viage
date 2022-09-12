#include <iostream>

#include <QQmlEngine>
#include <QDesktopServices>
#include <QLocale>
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
    , docxPath{tempPath + "/calcul.docx"}
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

    using namespace std;
    QFile rcs(":/data/calcul.docx");

    if (!rcs.copy(docxPath))
        mng->replyError("Calculation Document copy error", rcs.errorString());

    duckx::Document doc{docxPath.toStdString()};
    doc.open();

//    int i{0};
//    int j{0};
//    int k{0};
//    int l{0};
//    int m{0};
//    for (auto t = doc.tables(); t.has_next(); t.next())
//    {
//        cout << "tables :" << i << endl;
//        i++;
//        j = 0;
//         for (auto ro = t.rows(); ro.has_next(); ro.next())
//         {
//             cout << "__rows :" << j << endl;
//             j++;
//             k = 0;
//             for (auto c = ro.cells(); c.has_next(); c.next())
//             {
//                 cout << "____cells :" << k << endl;
//                 k++;
//                 l = 0;
//                 for (auto p = c.paragraphs(); p.has_next(); p.next())
//                 {
//                     cout << "______paragraps :" << l << endl;
//                     l++;
//                     m = 0;
//                     for (auto ru = p.runs(); ru.has_next(); ru.next())
//                     {
//                         cout << "________runs :" << m << endl;
//                         m++;
//                         cout << "________" << ru.get_text() << endl;
//                     }
//                 }
//             }
//         }
//     }

//    auto t{doc.tables()};
//    auto ro{t.rows()};
//    ro.next();
//    ro.next();
//    auto c{ro.cells()};
//    auto p{c.paragraphs()};
//    auto ru{p.runs()};
//    cout << ru.get_text() << endl;
}

void wrapped_calculator::calculate_rent()
{
    rent->from_expectency(exp.get_expectency(rent->getBirthDay()));
}

void wrapped_calculator::write_to_file()
{
    QFile file{docxPath};
    if (!file.exists())
    {
        QFile rcs(":/data/calcul.docx");

        if (!rcs.copy(docxPath))
            mng->replyError("Calculation Document copy error", rcs.errorString());
        // report error throug the net manager as it is connected to the bridge
    }

    file.setPermissions(QFileDevice::ReadOwner|QFileDevice::WriteOwner);

    duckx::Document doc{docxPath.toStdString()};
    doc.open();

    QString str{QDate::currentDate().toString("dd/MM/yyyy")};

    // skip to contract date
    auto t{doc.tables()};
    auto ro{t.rows()};
    ro.next();
    ro.next();
    auto c{ro.cells()};
    auto p{c.paragraphs()};
    auto ru{p.runs()};

    ru.set_text(str.toStdString());

    p = doc.paragraphs();

    // skip to pargraphs of interests
    for(int i{0}; i < 8; i++)
        p.next();

    ru = p.runs();

    str = tr("Date estimée de la transaction : ");
    str.append(rent->getBirthDay().toString("dd/MM/yyyy"));

    ru.set_text(str.toStdString());

    p.next();

    int i{0};
    for (const auto item : inner->items())
    {
        ru = p.runs();

        auto partner{inner->item_at(i)};
        QString sex{partner.sex == senior_citizen_item::M ? tr("M") : tr("Mme")};

        str = tr("Partenaire ");
        str.append(QString::number(i + 1));
        str.append(" : ");
        str.append(sex);
        str.append(" ……………………………………………………………… ");
        str.append(partner.birthDay.toString("dd/MM/yyyy"));

        ru.set_text(str.toStdString());

        p.next();
        i++;
    }

    // erase second partner paragraph
    if (i == 1)
    {
        ru = p.runs();
        ru.set_text("");
        p.next();
    }
    // skip address paragraph
    p.next();
    ru = p.runs();

    str = tr("Valeur estimée du bien : ");
    str.append(tr("CHF "));
    str.append(QLocale().toString(rent->getEstimation()));
    str.append(".-");
    str.append(tr("    Source : ……………………………"));

    ru.set_text(str.toStdString());

    p.next();
    ru = p.runs();

    str = tr("Droit d’habitation : ");
    str.append(tr("CHF "));
    str.append(QLocale().toString(rent->getDab()));
    str.append(".-");

    ru.set_text(str.toStdString());

    p.next();
    ru = p.runs();

    str = tr("Bouquet : ");
    str.append(tr("CHF "));
    str.append(QLocale().toString(rent->getBou()));
    str.append(".-");

    ru.set_text(str.toStdString());

    doc.save();
    file.setPermissions(QFileDevice::ReadOwner);
    if(!QDesktopServices::openUrl(docxPath))
        mng->replyError("Calculation Document error", "QDesktopervices : could not open .docx file");
}

}
