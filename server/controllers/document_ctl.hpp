#pragma once
#include <drogon/HttpController.h>

#include <s_document.hpp>
#include "full_controller.hpp"

using namespace drogon;

namespace Data
{
struct document_ctl final :
        public full_controller<document_ctl, s_list<s_document>, s_account, s_document>
{
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(document_ctl::insert, "/accounts/documents", Post);
    ADD_METHOD_TO(document_ctl::select, "/accounts/{}/documents", Get);
    ADD_METHOD_TO(document_ctl::update, "/documents", Put);
    ADD_METHOD_TO(document_ctl::update_from, "/accounts/documents", Put);
    ADD_METHOD_TO(document_ctl::remove, "/documents", Delete);
    METHOD_LIST_END

    void update(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr&)>&& callback) const;

    void remove(const HttpRequestPtr& req,
                std::function<void (const HttpResponsePtr&)>&& callback) const override;
};
}
