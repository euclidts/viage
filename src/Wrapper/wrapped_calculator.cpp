#include <iostream>

#include <QQmlEngine>
#include <QLocale>
#include <QFile>
#include <QJsonObject>
#ifndef EMSCRIPTEN
#include <QDesktopServices>
#else
#include <QFileDialog>
#endif

#include <src/client.hpp>
#include <Item/rent.hpp>
#include <netManager.hpp>
#include "wrapped_calculator.hpp"

namespace Calculator
{
wrapped_calculator::wrapped_calculator()
    : base_wrapper<list<senior_citizen>>{}
    , exp{inner}
    , rent_m{new Data::rent}
{
    inner->appendItems(); // at least one senior for the calculation

    this->connect(rent_m,
                  &rent::calculate,
                  this,
                  &wrapped_calculator::calculate_rent);

    this->connect(rent_m,
                  &rent::writeToFile,
                  this,
                  &wrapped_calculator::write_to_file);

    Interface::bridge::instance().context()->setContextProperty(Data::rent::key(), rent_m);

    if (client::is_german())
    {
        lingo = QLocale::German;
        docxName = "berechnung.docx";
    }
    else
    {
        lingo = QLocale().language();
        docxName = "calcul.docx";
    }

    docxPath += client::get_tempPath().toStdString() +'/' + docxName;

    QFile rcs(QString::fromStdString(":/data/" + docxName));

    // report error throug the net manager as it is connected to the bridge
    if (!rcs.copy(QString::fromStdString(docxPath)))
        Interface::netManager::instance().replyError("Calculation Document copy error",
                                                     rcs.errorString());

    // print_duckx();
}

const std::string wrapped_calculator::sex_string(const senior_citizen::sexes& sex)
{
    if (sex == senior_citizen::M)
        if (lingo == QLocale::German)
            return "Herr";
        else
            return "M  …";
    else
        if (lingo == QLocale::German)
            return "Frau";
        else
            return "Mme…";
}

void wrapped_calculator::calculate_rent()
{
    rent_m->from_expectency(exp.get_expectency(rent_m->getBirthDay()));
}

void wrapped_calculator::write_to_file()
{
    QJsonObject req;
    req["Lang"] = (lingo == QLocale::German) ? "German" : "French";
    auto partner{inner->item_at(0)};
    const std::string sex{sex_string(partner.sex)};

    QJsonObject person1;
    person1["Sex"] = partner.sex == 0 ? "M" : "F";
    person1["Birthdate"] = partner.birthDay.toString("yyyy/MM/dd");
    req["Person1"] = person1;
    if (inner->size() > 1)
    {
        auto partner2{inner->item_at(1)};
        QJsonObject person2;
        person2["Birthdate"] = partner2.birthDay.toString("yyyy/MM/dd");
        person2["Sex"] = partner2.sex == 0 ? "M" : "F";
        req["Person2"] = person2;
    }
    req["ValeurBien"] = rent_m->getmarketPrice();
    req["DateTransaction"] = rent_m->getBirthDay().toString("yyyy/MM/dd");






        QString path{client::get_tempPath() + "/calculUsufruit.docx"};
        QJsonDocument data{req};
        Interface::netManager::instance().downloadFilePost("Account/Usufruit",
                                                           data.toJson(),
                                                           path,
                                                           [this, &path] (bool success, const QString& error)
                                                           {
                                                               if (success)
                                                               {
#ifndef EMSCRIPTEN
                //file.setPermissions(QFileDevice::ReadOwner);

                if(!QDesktopServices::openUrl(QUrl::fromLocalFile(path)))
                    Interface::netManager::instance().replyError("Calculation Document error",
                                                                 "QDesktopervices : could not open .docx file");
#else
                QFile file(path);
                file.open(QFile::ReadOnly);
                QFileDialog::saveFileContent(file.readAll(), QString::fromStdString(docxName));
#endif
                                                               }
                                                               //else
                                                                   //onException("requestReport error", error);

                                                               //setDownloadProgress(-1.f);
                                                           },
                                                           [this](qint64 byteSent, qint64 totalbytes)
                                                           {
                                                               //setDownloadProgress((byteSent / 1024.) / (totalbytes / 1024.));
                                                               qDebug() << (byteSent / 1024.) / (totalbytes / 1024.);
                                                           });
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

}
