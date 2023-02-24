#ifndef UTILS_HPP
#define UTILS_HPP

#include <s_user.hpp>

namespace server
{
namespace utils
{
const std::string clearance_close(const Data::People::s_user& usr);
const std::string from_db_date(const std::string& db_date);
const std::string from_db_date_time(const std::string& db_date_time);
const std::string to_db_date(const std::string& raw_date, const std::string& format = "%d.%m.%Y");
const std::string update_flag(int flag, const std::string& flag_name, bool set);
}
}
#endif // UTILS_HPP
