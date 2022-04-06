#ifndef DATA_NOTIFYER_HPP
#define DATA_NOTIFYER_HPP

#include <QObject>
#include <wobjectdefs.h>

namespace Data
{
class data_notifyer : public QObject
{
    W_OBJECT(data_notifyer)

public:
    explicit data_notifyer();

    void validate(int parentIndex)
    W_SIGNAL(validate, parentIndex)

    void loadFrom(int parentIndex)
    W_SIGNAL(loadFrom, parentIndex)

    void loaded()
    W_SIGNAL(loaded)
};

}
#endif // DATA_NOTIFYER_HPP
