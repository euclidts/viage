/**
 *
 *  Basedefinition.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Basedefinition.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::viage;

const std::string Basedefinition::Cols::_Id = "Id";
const std::string Basedefinition::Cols::_ClassType = "ClassType";
const std::string Basedefinition::Cols::_Caption = "Caption";
const std::string Basedefinition::Cols::_Description = "Description";
const std::string Basedefinition::Cols::_IconKey = "IconKey";
const std::string Basedefinition::Cols::_DefinitionGroupId = "DefinitionGroupId";
const std::string Basedefinition::primaryKeyName = "";
const bool Basedefinition::hasPrimaryKey = false;
const std::string Basedefinition::tableName = "basedefinition";

const std::vector<typename Basedefinition::MetaData> Basedefinition::metaData_={
{"Id","int8_t","tinyint(4)",1,0,0,0},
{"ClassType","std::string","varchar(15)",15,0,0,0},
{"Caption","std::string","varchar(13)",13,0,0,0},
{"Description","std::string","varchar(218)",218,0,0,0},
{"IconKey","std::string","varchar(0)",0,0,0,0},
{"DefinitionGroupId","std::string","varchar(0)",0,0,0,0}
};
const std::string &Basedefinition::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Basedefinition::Basedefinition(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["Id"].isNull())
        {
            id_=std::make_shared<int8_t>(r["Id"].as<int8_t>());
        }
        if(!r["ClassType"].isNull())
        {
            classtype_=std::make_shared<std::string>(r["ClassType"].as<std::string>());
        }
        if(!r["Caption"].isNull())
        {
            caption_=std::make_shared<std::string>(r["Caption"].as<std::string>());
        }
        if(!r["Description"].isNull())
        {
            description_=std::make_shared<std::string>(r["Description"].as<std::string>());
        }
        if(!r["IconKey"].isNull())
        {
            iconkey_=std::make_shared<std::string>(r["IconKey"].as<std::string>());
        }
        if(!r["DefinitionGroupId"].isNull())
        {
            definitiongroupid_=std::make_shared<std::string>(r["DefinitionGroupId"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 6 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            id_=std::make_shared<int8_t>(r[index].as<int8_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            classtype_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            caption_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            description_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            iconkey_=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            definitiongroupid_=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

Basedefinition::Basedefinition(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int8_t>((int8_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            classtype_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            caption_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            description_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            iconkey_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            definitiongroupid_=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
        }
    }
}

Basedefinition::Basedefinition(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("Id"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["Id"].isNull())
        {
            id_=std::make_shared<int8_t>((int8_t)pJson["Id"].asInt64());
        }
    }
    if(pJson.isMember("ClassType"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["ClassType"].isNull())
        {
            classtype_=std::make_shared<std::string>(pJson["ClassType"].asString());
        }
    }
    if(pJson.isMember("Caption"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["Caption"].isNull())
        {
            caption_=std::make_shared<std::string>(pJson["Caption"].asString());
        }
    }
    if(pJson.isMember("Description"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["Description"].isNull())
        {
            description_=std::make_shared<std::string>(pJson["Description"].asString());
        }
    }
    if(pJson.isMember("IconKey"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["IconKey"].isNull())
        {
            iconkey_=std::make_shared<std::string>(pJson["IconKey"].asString());
        }
    }
    if(pJson.isMember("DefinitionGroupId"))
    {
        dirtyFlag_[5]=true;
        if(!pJson["DefinitionGroupId"].isNull())
        {
            definitiongroupid_=std::make_shared<std::string>(pJson["DefinitionGroupId"].asString());
        }
    }
}

void Basedefinition::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            id_=std::make_shared<int8_t>((int8_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            classtype_=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            caption_=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            description_=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            iconkey_=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            definitiongroupid_=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
        }
    }
}

void Basedefinition::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("Id"))
    {
        dirtyFlag_[0] = true;
        if(!pJson["Id"].isNull())
        {
            id_=std::make_shared<int8_t>((int8_t)pJson["Id"].asInt64());
        }
    }
    if(pJson.isMember("ClassType"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["ClassType"].isNull())
        {
            classtype_=std::make_shared<std::string>(pJson["ClassType"].asString());
        }
    }
    if(pJson.isMember("Caption"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["Caption"].isNull())
        {
            caption_=std::make_shared<std::string>(pJson["Caption"].asString());
        }
    }
    if(pJson.isMember("Description"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["Description"].isNull())
        {
            description_=std::make_shared<std::string>(pJson["Description"].asString());
        }
    }
    if(pJson.isMember("IconKey"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["IconKey"].isNull())
        {
            iconkey_=std::make_shared<std::string>(pJson["IconKey"].asString());
        }
    }
    if(pJson.isMember("DefinitionGroupId"))
    {
        dirtyFlag_[5] = true;
        if(!pJson["DefinitionGroupId"].isNull())
        {
            definitiongroupid_=std::make_shared<std::string>(pJson["DefinitionGroupId"].asString());
        }
    }
}

const int8_t &Basedefinition::getValueOfId() const noexcept
{
    const static int8_t defaultValue = int8_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<int8_t> &Basedefinition::getId() const noexcept
{
    return id_;
}
void Basedefinition::setId(const int8_t &pId) noexcept
{
    id_ = std::make_shared<int8_t>(pId);
    dirtyFlag_[0] = true;
}
void Basedefinition::setIdToNull() noexcept
{
    id_.reset();
    dirtyFlag_[0] = true;
}

const std::string &Basedefinition::getValueOfClasstype() const noexcept
{
    const static std::string defaultValue = std::string();
    if(classtype_)
        return *classtype_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Basedefinition::getClasstype() const noexcept
{
    return classtype_;
}
void Basedefinition::setClasstype(const std::string &pClasstype) noexcept
{
    classtype_ = std::make_shared<std::string>(pClasstype);
    dirtyFlag_[1] = true;
}
void Basedefinition::setClasstype(std::string &&pClasstype) noexcept
{
    classtype_ = std::make_shared<std::string>(std::move(pClasstype));
    dirtyFlag_[1] = true;
}
void Basedefinition::setClasstypeToNull() noexcept
{
    classtype_.reset();
    dirtyFlag_[1] = true;
}

const std::string &Basedefinition::getValueOfCaption() const noexcept
{
    const static std::string defaultValue = std::string();
    if(caption_)
        return *caption_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Basedefinition::getCaption() const noexcept
{
    return caption_;
}
void Basedefinition::setCaption(const std::string &pCaption) noexcept
{
    caption_ = std::make_shared<std::string>(pCaption);
    dirtyFlag_[2] = true;
}
void Basedefinition::setCaption(std::string &&pCaption) noexcept
{
    caption_ = std::make_shared<std::string>(std::move(pCaption));
    dirtyFlag_[2] = true;
}
void Basedefinition::setCaptionToNull() noexcept
{
    caption_.reset();
    dirtyFlag_[2] = true;
}

const std::string &Basedefinition::getValueOfDescription() const noexcept
{
    const static std::string defaultValue = std::string();
    if(description_)
        return *description_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Basedefinition::getDescription() const noexcept
{
    return description_;
}
void Basedefinition::setDescription(const std::string &pDescription) noexcept
{
    description_ = std::make_shared<std::string>(pDescription);
    dirtyFlag_[3] = true;
}
void Basedefinition::setDescription(std::string &&pDescription) noexcept
{
    description_ = std::make_shared<std::string>(std::move(pDescription));
    dirtyFlag_[3] = true;
}
void Basedefinition::setDescriptionToNull() noexcept
{
    description_.reset();
    dirtyFlag_[3] = true;
}

const std::string &Basedefinition::getValueOfIconkey() const noexcept
{
    const static std::string defaultValue = std::string();
    if(iconkey_)
        return *iconkey_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Basedefinition::getIconkey() const noexcept
{
    return iconkey_;
}
void Basedefinition::setIconkey(const std::string &pIconkey) noexcept
{
    iconkey_ = std::make_shared<std::string>(pIconkey);
    dirtyFlag_[4] = true;
}
void Basedefinition::setIconkey(std::string &&pIconkey) noexcept
{
    iconkey_ = std::make_shared<std::string>(std::move(pIconkey));
    dirtyFlag_[4] = true;
}
void Basedefinition::setIconkeyToNull() noexcept
{
    iconkey_.reset();
    dirtyFlag_[4] = true;
}

const std::string &Basedefinition::getValueOfDefinitiongroupid() const noexcept
{
    const static std::string defaultValue = std::string();
    if(definitiongroupid_)
        return *definitiongroupid_;
    return defaultValue;
}
const std::shared_ptr<std::string> &Basedefinition::getDefinitiongroupid() const noexcept
{
    return definitiongroupid_;
}
void Basedefinition::setDefinitiongroupid(const std::string &pDefinitiongroupid) noexcept
{
    definitiongroupid_ = std::make_shared<std::string>(pDefinitiongroupid);
    dirtyFlag_[5] = true;
}
void Basedefinition::setDefinitiongroupid(std::string &&pDefinitiongroupid) noexcept
{
    definitiongroupid_ = std::make_shared<std::string>(std::move(pDefinitiongroupid));
    dirtyFlag_[5] = true;
}
void Basedefinition::setDefinitiongroupidToNull() noexcept
{
    definitiongroupid_.reset();
    dirtyFlag_[5] = true;
}

void Basedefinition::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Basedefinition::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "Id",
        "ClassType",
        "Caption",
        "Description",
        "IconKey",
        "DefinitionGroupId"
    };
    return inCols;
}

void Basedefinition::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getClasstype())
        {
            binder << getValueOfClasstype();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCaption())
        {
            binder << getValueOfCaption();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIconkey())
        {
            binder << getValueOfIconkey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getDefinitiongroupid())
        {
            binder << getValueOfDefinitiongroupid();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Basedefinition::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    return ret;
}

void Basedefinition::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getClasstype())
        {
            binder << getValueOfClasstype();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getCaption())
        {
            binder << getValueOfCaption();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getIconkey())
        {
            binder << getValueOfIconkey();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getDefinitiongroupid())
        {
            binder << getValueOfDefinitiongroupid();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Basedefinition::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["Id"]=getValueOfId();
    }
    else
    {
        ret["Id"]=Json::Value();
    }
    if(getClasstype())
    {
        ret["ClassType"]=getValueOfClasstype();
    }
    else
    {
        ret["ClassType"]=Json::Value();
    }
    if(getCaption())
    {
        ret["Caption"]=getValueOfCaption();
    }
    else
    {
        ret["Caption"]=Json::Value();
    }
    if(getDescription())
    {
        ret["Description"]=getValueOfDescription();
    }
    else
    {
        ret["Description"]=Json::Value();
    }
    if(getIconkey())
    {
        ret["IconKey"]=getValueOfIconkey();
    }
    else
    {
        ret["IconKey"]=Json::Value();
    }
    if(getDefinitiongroupid())
    {
        ret["DefinitionGroupId"]=getValueOfDefinitiongroupid();
    }
    else
    {
        ret["DefinitionGroupId"]=Json::Value();
    }
    return ret;
}

Json::Value Basedefinition::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 6)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getClasstype())
            {
                ret[pMasqueradingVector[1]]=getValueOfClasstype();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getCaption())
            {
                ret[pMasqueradingVector[2]]=getValueOfCaption();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getDescription())
            {
                ret[pMasqueradingVector[3]]=getValueOfDescription();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getIconkey())
            {
                ret[pMasqueradingVector[4]]=getValueOfIconkey();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getDefinitiongroupid())
            {
                ret[pMasqueradingVector[5]]=getValueOfDefinitiongroupid();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["Id"]=getValueOfId();
    }
    else
    {
        ret["Id"]=Json::Value();
    }
    if(getClasstype())
    {
        ret["ClassType"]=getValueOfClasstype();
    }
    else
    {
        ret["ClassType"]=Json::Value();
    }
    if(getCaption())
    {
        ret["Caption"]=getValueOfCaption();
    }
    else
    {
        ret["Caption"]=Json::Value();
    }
    if(getDescription())
    {
        ret["Description"]=getValueOfDescription();
    }
    else
    {
        ret["Description"]=Json::Value();
    }
    if(getIconkey())
    {
        ret["IconKey"]=getValueOfIconkey();
    }
    else
    {
        ret["IconKey"]=Json::Value();
    }
    if(getDefinitiongroupid())
    {
        ret["DefinitionGroupId"]=getValueOfDefinitiongroupid();
    }
    else
    {
        ret["DefinitionGroupId"]=Json::Value();
    }
    return ret;
}

bool Basedefinition::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("Id"))
    {
        if(!validJsonOfField(0, "Id", pJson["Id"], err, true))
            return false;
    }
    if(pJson.isMember("ClassType"))
    {
        if(!validJsonOfField(1, "ClassType", pJson["ClassType"], err, true))
            return false;
    }
    if(pJson.isMember("Caption"))
    {
        if(!validJsonOfField(2, "Caption", pJson["Caption"], err, true))
            return false;
    }
    if(pJson.isMember("Description"))
    {
        if(!validJsonOfField(3, "Description", pJson["Description"], err, true))
            return false;
    }
    if(pJson.isMember("IconKey"))
    {
        if(!validJsonOfField(4, "IconKey", pJson["IconKey"], err, true))
            return false;
    }
    if(pJson.isMember("DefinitionGroupId"))
    {
        if(!validJsonOfField(5, "DefinitionGroupId", pJson["DefinitionGroupId"], err, true))
            return false;
    }
    return true;
}
bool Basedefinition::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                        const std::vector<std::string> &pMasqueradingVector,
                                                        std::string &err)
{
    if(pMasqueradingVector.size() != 6)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty())
      {
          if(pJson.isMember(pMasqueradingVector[0]))
          {
              if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[1].empty())
      {
          if(pJson.isMember(pMasqueradingVector[1]))
          {
              if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[2].empty())
      {
          if(pJson.isMember(pMasqueradingVector[2]))
          {
              if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[3].empty())
      {
          if(pJson.isMember(pMasqueradingVector[3]))
          {
              if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[4].empty())
      {
          if(pJson.isMember(pMasqueradingVector[4]))
          {
              if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                  return false;
          }
      }
      if(!pMasqueradingVector[5].empty())
      {
          if(pJson.isMember(pMasqueradingVector[5]))
          {
              if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, true))
                  return false;
          }
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Basedefinition::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("Id"))
    {
        if(!validJsonOfField(0, "Id", pJson["Id"], err, false))
            return false;
    }
    if(pJson.isMember("ClassType"))
    {
        if(!validJsonOfField(1, "ClassType", pJson["ClassType"], err, false))
            return false;
    }
    if(pJson.isMember("Caption"))
    {
        if(!validJsonOfField(2, "Caption", pJson["Caption"], err, false))
            return false;
    }
    if(pJson.isMember("Description"))
    {
        if(!validJsonOfField(3, "Description", pJson["Description"], err, false))
            return false;
    }
    if(pJson.isMember("IconKey"))
    {
        if(!validJsonOfField(4, "IconKey", pJson["IconKey"], err, false))
            return false;
    }
    if(pJson.isMember("DefinitionGroupId"))
    {
        if(!validJsonOfField(5, "DefinitionGroupId", pJson["DefinitionGroupId"], err, false))
            return false;
    }
    return true;
}
bool Basedefinition::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                      const std::vector<std::string> &pMasqueradingVector,
                                                      std::string &err)
{
    if(pMasqueradingVector.size() != 6)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
      if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
      {
          if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
              return false;
      }
      if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
      {
          if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
              return false;
      }
      if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
      {
          if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
              return false;
      }
      if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
      {
          if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
              return false;
      }
      if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
      {
          if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
              return false;
      }
      if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
      {
          if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, false))
              return false;
      }
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Basedefinition::validJsonOfField(size_t index,
                                      const std::string &fieldName,
                                      const Json::Value &pJson,
                                      std::string &err,
                                      bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 15)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 15)";
                return false;
            }

            break;
        case 2:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 13)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 13)";
                return false;
            }

            break;
        case 3:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 218)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    " field (the maximum value is 218)";
                return false;
            }

            break;
        case 4:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 5:
            if(pJson.isNull())
            {
                return true;
            }
            if(!pJson.isString())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
