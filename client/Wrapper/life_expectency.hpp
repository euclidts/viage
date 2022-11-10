#ifndef EXPECTENCY
#define EXPECTENCY

#include <QDate>

#include <Item/senior_citizen_item.hpp>

namespace Data
{
template <typename T>
class simple_item_list;
}

namespace Calculator
{
using namespace Data;
using namespace People;

class life_expectency
{
public:
    explicit life_expectency(simple_item_list<senior_citizen_item>* senior_citizens);

    double get_expectency(const QDate& date);

private:
    simple_item_list<senior_citizen_item>* seniors;

    struct dto
    {
        dto() {};
        dto(const senior_citizen_item& senior, const QDate& date)
            : sex{senior.sex}
            , thousand_bDAy{senior.birthDay.year() * 1000}
            , age{senior.birthDay.daysTo(date) / 365.25}
            , age_trunc{std::trunc(age)}
            , age_diff{age - age_trunc}
        {}
        senior_citizen_item::sexes sex{senior_citizen_item::M};
        int thousand_bDAy{0};
        double age{0};
        double age_trunc{0};
        double age_diff{0};
    };

    std::map<int, std::array<double, 2>> mortality{};
    int mortality_offset{0};

    void readMortality(const QString& path);
    double get_mortality();

    double get_pers(const dto& d, int index, int plus = 0);
    double get_qx(const dto& d, int index);
};

}

#endif // EXPECTENCY
