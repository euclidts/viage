#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <QTemporaryDir>

#include <Item/c_account.hpp>
#include <Item/c_owner.hpp>
#include <Item/c_user.hpp>
#include <Item/c_company.hpp>
#include <Item/c_team.hpp>

namespace Calculator
{
class wrapped_calculator;
}

namespace Wrapper
{
template <typename T>
class wrapped_list;

template <typename Inner, typename Outer>
class wrapped_nested_list;

template <typename Inner, typename Outer>
class wrapped_nested_item;
}

class client final
{
public:
    static client& instance();
    void init();

    client(client const&) = delete;
    void operator = (client const&) = delete;

    Data::c_list<Data::c_account>* get_accounts() const;
    Data::c_list<Data::c_document>* get_documents() const;
    Data::c_list<Data::People::c_user>* get_users() const;

    static const QTemporaryDir tempDir;
    static const QString get_tempPath();

private:
    client() {};

    Calculator::wrapped_calculator* calculator;

    Wrapper::wrapped_list<Data::c_list<Data::c_account>>* accounts;
    Wrapper::wrapped_nested_list<Data::c_list<Data::People::c_owner>, Data::c_account>* owners;
    Wrapper::wrapped_nested_list<Data::c_list<Data::People::c_contact>, Data::c_account>* contacts;
    Wrapper::wrapped_nested_item<Data::Places::c_habitat, Data::c_account>* habitat;
    Wrapper::wrapped_nested_item<Data::Places::c_exterior, Data::c_account>* exterior;
    Wrapper::wrapped_nested_list<Data::c_list<Data::c_document>, Data::c_account>* documents;

    Wrapper::wrapped_list<Data::c_list<Data::People::c_user>>* users;
    Wrapper::wrapped_list<Data::c_list<Data::c_company>>* companies;
    Wrapper::wrapped_list<Data::c_list<Data::c_team>>* teams;
};


#endif // CLIENT_HPP
