#ifndef C_BASE_DATA_HPP
#define C_BASE_DATA_HPP

#include <QObject>
#include <wobjectdefs.h>

#include <base_data.hpp>

namespace Data
{
class c_base_data : public QObject
                  , virtual public base_data
{
    W_OBJECT(c_base_data)

public:
    void validate(int id)
    W_SIGNAL(validate, id)

    void loadFrom(int id)
    W_SIGNAL(loadFrom, id)

    void loaded()
    W_SIGNAL(loaded)

    const QByteArray toData(const char* parentKey, int parnetId);
    const QByteArray toData(int parnetId);

    virtual void read(const QByteArray& bytes);

    bool getCompleted() const;
    void setCompleted(bool newCompleted);

    void completedChanged()
    W_SIGNAL(completedChanged)

    W_PROPERTY(bool, completed READ getCompleted NOTIFY completedChanged)

protected:
    explicit c_base_data(QObject* parent = nullptr);

    bool completed;
    virtual void checkCompleted() {};
};

}
#endif // C_BASE_DATA_HPP
