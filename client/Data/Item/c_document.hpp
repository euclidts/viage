#ifndef C_DOCUMENT_HPP
#define C_DOCUMENT_HPP

#include "qnamespace.h"
#include <Item/document_item.hpp>

namespace Data
{
struct c_document : public document_item
{
    c_document();

    static const constexpr auto qmlName{"Document"};
    static const constexpr auto uri{"Data"};

    enum roles
    {
        CategoryRole = Qt::UserRole,
        RelativePathRole,
        LocalPathRole,
        FileNameRole,
        ExtensionRole,
        StateRole,
        UploadProgressRole,
        UploadDateRole,
        IdRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);
};

}

#endif // C_DOCUMENT_HPP
