#ifndef RENTCALCULATOR_HPP
#define RENTCALCULATOR_HPP

#include <QDate>

#include <Items/infant_item.hpp> // needed for Sex enum

#define AGE_MIN 65
#define AGE_MAX 120

namespace Calculator
{
namespace Expectency
{
class individual
{
public:
    individual();

    double get_expectency();

    const QDate &getBirthDay() const;
    void setBirthDay(const QDate &newBirthDay);

    Data::People::infant_item::sexes sex{Data::People::infant_item::M};

private:
    QDate birthDay;
    int thousand_bDAy{0};
    double age{0};
    double age_trunc{0};
    double age_diff{0};

    std::map<int, double> mortality{};
    int mortality_offset{0};

    void readMortality(const QString& path);
    double get_mortality();

    double get_pers(int index = 0, int plus = 0);
    double get_qx(int index = 0);
};

}

}

#endif // RENTCALCULATOR_HPP
