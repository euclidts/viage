#include <QFile>

#include "life_expectency.hpp"
#include <Items/senior_citizen_item.hpp> // needed for sexes enum

namespace Calculator
{

expectency::expectency()
{
    readMortality(":/ofs.csv");

//    thousand_bDAy = birthDay.year() * 1000;
//    age = birthDay.daysTo(QDate::currentDate()) / 365.25;
//    age_trunc = std::trunc(age);
//    age_diff = age - std::round(age);
}

void expectency::readMortality(const QString& path)
{
    QFile csv{path};

    if (!csv.open(QIODevice::ReadOnly))
    {
        qDebug() << "readMortality error :" << csv.errorString();
        return;
    }

    while (!csv.atEnd())
    {
        auto line{csv.readLine()};
        auto splitedLine{line.split(',')};

//        mortality[splitedLine[2].toInt()] = splitedLine[3 + sex].toDouble();
    }
}

double expectency::get_expectency()
{
    double lx{1};
    double ex{0};

    for (int i = 0; i <= 126; i++)
    {
        ex += lx;
        lx = lx * (1 - get_qx(i));
    }

    ex -= 0.5;
    return ex;
}

double expectency::get_pers(int index, int plus)
{
    int add = age_trunc + index + plus;
    int key = thousand_bDAy + std::min(add, AGE_MAX);
    return mortality[key];
}

double expectency::get_qx(int index)
{
    return age_diff * get_pers(index, 1) + (1 - age_diff) * get_pers(index);
}

}
