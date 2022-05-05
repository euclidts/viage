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

    void validate(int id)
    W_SIGNAL(validate, id)

    void loadFrom(int id)
    W_SIGNAL(loadFrom, id)

    void loaded()
    W_SIGNAL(loaded)

    const QByteArray toData(const char* parentKey, int parnetId);
    const QByteArray toData(int parnetId);

protected:
    explicit base_data(QObject* parent = nullptr);

    virtual void writeWithKey(QJsonObject& json) {};
};

}
#endif // BASE_DATA_HPP
