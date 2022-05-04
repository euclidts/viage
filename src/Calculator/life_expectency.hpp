#ifndef EXPECTENCY
#define EXPECTENCY

#include <QDate>

#include <Items/infant_item.hpp> // needed for Sex enum

namespace Calculator
{

class expectency
{
public:
    expectency();

    double get_expectency();

private:
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

#endif // EXPECTENCY
