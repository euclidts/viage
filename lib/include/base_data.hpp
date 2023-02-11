#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP

#include <json/json.h>

namespace Data
{
enum complitions
{
    Incomplete = 0,
    Complete,
    Empty
};

template <typename T>
class base_data
{
public:
    virtual void read(const Json::Value& json) {};
    virtual void write(Json::Value& json) const {};

    virtual complitions complition() const { return Complete; };
    virtual void clear() {};

protected:
    explicit base_data() {};

    virtual void writeWithKey(Json::Value& json) const
    {
        Json::Value obj;
        write(obj);

        json[T::key] = obj;
    }
};
}

#endif // BASE_DATA_HPP
