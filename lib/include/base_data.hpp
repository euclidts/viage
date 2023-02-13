#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP

#include <json/json.h>

namespace Data
{
template <typename T>
class base_data
{
public:
    virtual void read(const Json::Value& json) {};
    virtual void write(Json::Value& json) const {};

    virtual bool is_completed() const { return false; };
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
