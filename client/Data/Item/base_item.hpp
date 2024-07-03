#ifndef BASE_ITEM_HPP
#define BASE_ITEM_HPP

#include <QJsonObject>
#include <QJsonDocument>

namespace Data
{
template <typename T>
class base_item
{
public:
    virtual void write(QJsonObject &) const = 0;

    const QByteArray toData(const char* parentKey, int parentId)
    {
        QString str{parentKey};
        str.append("Id");

        QJsonObject data{ {str, parentId} };

        writeWithKey(data);

        QJsonDocument bytes{data};
        return bytes.toJson();
    }

    const QByteArray toData(int parentId)
    {
        QJsonObject data{ {"Id", parentId} };

        writeWithKey(data);

        QJsonDocument bytes{data};
        return bytes.toJson();
    }

    virtual bool is_completed() const { return true; }

protected:
    explicit base_item() = default;

    virtual void writeWithKey(QJsonObject& json)
    {
        QJsonObject obj{};
        write(obj);

        json[T::key()] = obj;
    }

    virtual void checkCompleted() {}
};
}

#endif // BASE_ITEM_HPP
