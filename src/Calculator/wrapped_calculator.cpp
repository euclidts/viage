#include <iostream>

#include <QQmlEngine>
#include <QDesktopServices>
#include <QLocale>
#include <QFile>

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

    QFile rcs(":/data/calcul.docx");

    if (!rcs.copy(docxPath))
        mng->replyError("Calculation Document copy error", rcs.errorString());
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
    ro.next();
    auto c{ro.cells()};
    auto p{c.paragraphs()};
    auto ru{p.runs()};

    ru.set_text(str.toStdString());

    p = doc.paragraphs();

    // skip to pargraphs of interests
    skip_paragraphs(p, 4);

    ru = p.runs();
    ru.next();

    str = rent->getBirthDay().toString("dd/MM/yyyy");
    ru.set_text(str.toStdString());

    end_runs(ru);
    p.next();

    int i{0};
    for (const auto item : inner->items())
    {
        ru = p.runs();
        skip_runs(ru, 2);

        auto partner{inner->item_at(i)};
        QString sex{partner.sex == senior_citizen_item::M ? tr("M  …") : tr("Mme")};
        ru.set_text(sex.toStdString());
        skip_runs(ru, 2);

        ru.set_text("……………………………………………………………");
        ru.next();

        str = partner.birthDay.toString("dd/MM/yyyy");
        ru.set_text(str.toStdString());
        end_runs(ru);

        p.next();
        i++;
    }

    // erase second partner paragraph
    if (i == 1)
    {
        ru = p.runs();
        ru.set_text("");
        end_runs(ru);
        p.next();
    }

    // skip to pargraphs of interests
    skip_paragraphs(p, 3);

    ru = p.runs();

    skip_runs(ru, 7);

    str = QLocale().toString(rent->getmarketPrice());
    str.append(".-");
    ru.set_text(str.toStdString());

    end_runs(ru);
    p.next();
    ru = p.runs();

    skip_runs(ru, 8);

    str = QLocale().toString(rent->getDab());
    str.append(".-");
    ru.set_text(str.toStdString());

    end_runs(ru);
    p.next();
    ru = p.runs();

    skip_runs(ru, 9);

    str = QLocale().toString(rent->getBou());
    str.append(".-");
    ru.set_text(str.toStdString());

    end_runs(ru);

    doc.save();
    file.setPermissions(QFileDevice::ReadOwner);
    if(!QDesktopServices::openUrl(docxPath))
        mng->replyError("Calculation Document error", "QDesktopervices : could not open .docx file");
}

void wrapped_calculator::end_runs(duckx::Run& run)
{
    run.next();

    for (; run.has_next(); run.next())
        run.set_text("");
}

void wrapped_calculator::skip_paragraphs(duckx::Paragraph& paragraphs, int n_skiped)
{
    for(int i{0}; i < n_skiped; i++)
        paragraphs.next();
}

void wrapped_calculator::skip_runs(duckx::Run& runs, int n_skiped)
{
    for(int i{0}; i < n_skiped; i++)
        runs.next();
}

void wrapped_calculator::print_runs(duckx::Run& runs)
{
    for (; runs.has_next(); runs.next())
        std::cout << runs.get_text() << std::endl;
}

void wrapped_calculator::print_duckx()
{
    duckx::Document doc{docxPath.toStdString()};
    doc.open();

    using namespace std;

    int i{0};
    int j{0};
    int k{0};
    int l{0};
    int m{0};
    for (auto t = doc.tables(); t.has_next(); t.next())
    {
        cout << "tables :" << i << endl;
        i++;
        j = 0;
        for (auto ro = t.rows(); ro.has_next(); ro.next())
        {
            cout << "__rows :" << j << endl;
            j++;
            k = 0;
            for (auto c = ro.cells(); c.has_next(); c.next())
            {
                cout << "____cells :" << k << endl;
                k++;
                l = 0;
                for (auto p = c.paragraphs(); p.has_next(); p.next())
                {
                    cout << "______paragraps :" << l << endl;
                    l++;
                    m = 0;
                    for (auto ru = p.runs(); ru.has_next(); ru.next())
                    {
                        cout << "________runs :" << m << endl;
                        m++;
                        cout << "________" << ru.get_text() << endl;
                    }
                }
            }
        }
    }

    auto t{doc.tables()};
    auto ro{t.rows()};
    ro.next();
    ro.next();
    auto c{ro.cells()};
    auto p{c.paragraphs()};
    auto ru{p.runs()};
    cout << ru.get_text() << endl;
}
}
