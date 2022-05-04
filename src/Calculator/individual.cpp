#include <QFile>

#include "individual.hpp"

namespace Calculator
{
namespace Expectency
{
individual::individual()
{
    readMortality(":/ofs.csv");
}

void individual::readMortality(const QString& path)
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
        auto splitedLine{line.split(';')};

        mortality[splitedLine[2].toInt()] = splitedLine[3 + sex].toDouble();
    }
}

double individual::get_expectency()
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

const QDate &individual::getBirthDay() const
{
    return birthDay;
}

void individual::setBirthDay(const QDate &newBirthDay)
{
    birthDay = newBirthDay;
    thousand_bDAy = birthDay.year() * 1000;
    age = birthDay.daysTo(QDate::currentDate()) / 365.25;
    age_trunc = std::trunc(age);
    age_diff = age - std::round(age);
}

double individual::get_pers(int index, int plus)
{
    int add = age_trunc + index + plus;
    int key = thousand_bDAy + std::min(add, AGE_MAX);
    return mortality[key];
}

double individual::get_qx(int index)
{
    return age_diff * get_pers(index, 1) + (1 - age_diff) * get_pers(index);
}

}

}
