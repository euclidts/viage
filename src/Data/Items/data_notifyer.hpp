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
    virtual const constexpr char* key() = 0;

    virtual void write(QJsonObject &json) const {};
    const QByteArray toData(const char* parentKey, int parnetId);

    void validate(int parentIndex)
    W_SIGNAL(validate, parentIndex)

    void loadFrom(int parentIndex)
    W_SIGNAL(loadFrom, parentIndex)

    void loaded()
    W_SIGNAL(loaded)

protected:
    explicit data_notifyer(QObject* = nullptr);
};

}
#endif // DATA_NOTIFYER_HPP
