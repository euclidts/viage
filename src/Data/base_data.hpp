#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP

#include <QObject>
#include <wobjectdefs.h>

namespace Data
{
class base_data : public QObject
{
    W_OBJECT(base_data)

public:
    virtual const constexpr char* key() = 0;

    void validate(int parentIndex)
    W_SIGNAL(validate, parentIndex)

    void loadFrom(int parentIndex)
    W_SIGNAL(loadFrom, parentIndex)

    void loaded()
    W_SIGNAL(loaded)

    const QByteArray toData(const char* parentKey, int parnetId);

protected:
    explicit base_data(QObject* parent = nullptr);

    virtual void writeWithKey(QJsonObject& json) {};
};

}
#endif // BASE_DATA_HPP
