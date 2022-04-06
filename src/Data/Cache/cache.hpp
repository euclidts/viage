#ifndef CACHE_HPP
#define CACHE_HPP

#include <QJsonObject>
#include <QQmlContext>

#include <wobjectdefs.h>

namespace Data
{

namespace Cache
{
class cache final
        : public QObject
        , public QJsonObject
{
    W_OBJECT(cache)

    public:
        explicit cache();

    template<typename T>
    void update(const char* parentKey,
                int index,
                const T& element,
                const char* key);

    template<typename T>
    void update(int index,
                const T& element,
                const char* key);

private:
    void print() const;
};

}
}

#include "cache.cpp"
#endif // CACHE_HPP
