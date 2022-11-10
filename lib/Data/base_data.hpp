#ifndef BASE_DATA_HPP
#define BASE_DATA_HPP

#include <json/json.h>

namespace Data
{
class base_data
{
public:
    virtual const constexpr char* key() const = 0;

    virtual void read(const Json::Value& json) {};
    virtual void write(Json::Value& json) const {};

    virtual bool is_completed() const { return true; };
    virtual void clear() {};

protected:
    explicit base_data();

    virtual void writeWithKey(Json::Value& json) const;
};

}
#endif // BASE_DATA_HPP
