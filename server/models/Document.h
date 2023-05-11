/**
 *
 *  Document.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#ifdef __cpp_impl_coroutine
#include <drogon/orm/CoroMapper.h>
#endif
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <json/json.h>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}
}
namespace drogon_model
{
namespace viage
{

class Document
{
  public:
    struct Cols
    {
        static const std::string _Id;
        static const std::string _Category;
        static const std::string _Extension;
        static const std::string _FileName;
        static const std::string _RelativePath;
        static const std::string _IsUploaded;
        static const std::string _UploadDate;
        static const std::string _AccountId;
        static const std::string _IsProcessed;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    using PrimaryKeyType = void;
    int getPrimaryKey() const { assert(false); return 0; }

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names,
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all
     * columns by an asterisk), please set the offset to -1.
     */
    explicit Document(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Document(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Document(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Document() = default;

    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    static bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForCreation(const Json::Value &,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                    std::string &err);
    static bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    static bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    static bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson,
                          std::string &err,
                          bool isForCreation);

    /**  For column Id  */
    ///Get the value of the column Id, returns the default value if the column is null
    const int16_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int16_t> &getId() const noexcept;
    ///Set the value of the column Id
    void setId(const int16_t &pId) noexcept;
    void setIdToNull() noexcept;

    /**  For column Category  */
    ///Get the value of the column Category, returns the default value if the column is null
    const int16_t &getValueOfCategory() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int16_t> &getCategory() const noexcept;
    ///Set the value of the column Category
    void setCategory(const int16_t &pCategory) noexcept;
    void setCategoryToNull() noexcept;

    /**  For column Extension  */
    ///Get the value of the column Extension, returns the default value if the column is null
    const std::string &getValueOfExtension() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getExtension() const noexcept;
    ///Set the value of the column Extension
    void setExtension(const std::string &pExtension) noexcept;
    void setExtension(std::string &&pExtension) noexcept;
    void setExtensionToNull() noexcept;

    /**  For column FileName  */
    ///Get the value of the column FileName, returns the default value if the column is null
    const std::string &getValueOfFilename() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getFilename() const noexcept;
    ///Set the value of the column FileName
    void setFilename(const std::string &pFilename) noexcept;
    void setFilename(std::string &&pFilename) noexcept;
    void setFilenameToNull() noexcept;

    /**  For column RelativePath  */
    ///Get the value of the column RelativePath, returns the default value if the column is null
    const std::string &getValueOfRelativepath() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getRelativepath() const noexcept;
    ///Set the value of the column RelativePath
    void setRelativepath(const std::string &pRelativepath) noexcept;
    void setRelativepath(std::string &&pRelativepath) noexcept;
    void setRelativepathToNull() noexcept;

    /**  For column IsUploaded  */
    ///Get the value of the column IsUploaded, returns the default value if the column is null
    const int8_t &getValueOfIsuploaded() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int8_t> &getIsuploaded() const noexcept;
    ///Set the value of the column IsUploaded
    void setIsuploaded(const int8_t &pIsuploaded) noexcept;
    void setIsuploadedToNull() noexcept;

    /**  For column UploadDate  */
    ///Get the value of the column UploadDate, returns the default value if the column is null
    const std::string &getValueOfUploaddate() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getUploaddate() const noexcept;
    ///Set the value of the column UploadDate
    void setUploaddate(const std::string &pUploaddate) noexcept;
    void setUploaddate(std::string &&pUploaddate) noexcept;
    void setUploaddateToNull() noexcept;

    /**  For column AccountId  */
    ///Get the value of the column AccountId, returns the default value if the column is null
    const int8_t &getValueOfAccountid() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int8_t> &getAccountid() const noexcept;
    ///Set the value of the column AccountId
    void setAccountid(const int8_t &pAccountid) noexcept;
    void setAccountidToNull() noexcept;

    /**  For column IsProcessed  */
    ///Get the value of the column IsProcessed, returns the default value if the column is null
    const int8_t &getValueOfIsprocessed() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int8_t> &getIsprocessed() const noexcept;
    ///Set the value of the column IsProcessed
    void setIsprocessed(const int8_t &pIsprocessed) noexcept;
    void setIsprocessedToNull() noexcept;


    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;
    /// Relationship interfaces
  private:
    friend drogon::orm::Mapper<Document>;
#ifdef __cpp_impl_coroutine
    friend drogon::orm::CoroMapper<Document>;
#endif
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int16_t> id_;
    std::shared_ptr<int16_t> category_;
    std::shared_ptr<std::string> extension_;
    std::shared_ptr<std::string> filename_;
    std::shared_ptr<std::string> relativepath_;
    std::shared_ptr<int8_t> isuploaded_;
    std::shared_ptr<std::string> uploaddate_;
    std::shared_ptr<int8_t> accountid_;
    std::shared_ptr<int8_t> isprocessed_;
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
    static const std::vector<MetaData> metaData_;
    bool dirtyFlag_[9]={ false };
  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="";
        return sql;
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="";
        return sql;
    }
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
        if(dirtyFlag_[0])
        {
            sql += "Id,";
            ++parametersCount;
        }
        if(dirtyFlag_[1])
        {
            sql += "Category,";
            ++parametersCount;
        }
        if(dirtyFlag_[2])
        {
            sql += "Extension,";
            ++parametersCount;
        }
        if(dirtyFlag_[3])
        {
            sql += "FileName,";
            ++parametersCount;
        }
        if(dirtyFlag_[4])
        {
            sql += "RelativePath,";
            ++parametersCount;
        }
        if(dirtyFlag_[5])
        {
            sql += "IsUploaded,";
            ++parametersCount;
        }
        if(dirtyFlag_[6])
        {
            sql += "UploadDate,";
            ++parametersCount;
        }
        if(dirtyFlag_[7])
        {
            sql += "AccountId,";
            ++parametersCount;
        }
        if(dirtyFlag_[8])
        {
            sql += "IsProcessed,";
            ++parametersCount;
        }
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";

        if(dirtyFlag_[0])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[1])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[2])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[3])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[4])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[5])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[6])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[7])
        {
            sql.append("?,");

        }
        if(dirtyFlag_[8])
        {
            sql.append("?,");

        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        sql.append(1, ')');
        LOG_TRACE << sql;
        return sql;
    }
};
} // namespace viage
} // namespace drogon_model
