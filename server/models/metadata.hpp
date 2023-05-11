#ifndef METADATA_HPP
#define METADATA_HPP

#include <string>

namespace drogon_model
{
struct MetaData
{
    const std::string colName_;
    const std::string colType_;
    const std::string colDatabaseType_;
    const ssize_t colLength_;
    const bool isAutoVal_;
    const bool isPrimaryKey_;
    const bool notNull_;
};
}
#endif // METADATA_HPP
