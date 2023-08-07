#ifndef PROFESSIONAL_STL_BANK_H
#define PROFESSIONAL_STL_BANK_H

#include <string>
#include <map>

class bank_account
{
public:
    bank_account(int number, std::string name) : account_number_(number), client_name_(std::move(name)) {}

    int get_account_number() const
    {
        return account_number_;
    }

    void set_account_number(int number)
    {
        account_number_ = number;
    }

    const std::string &get_client_name() const
    {
        return client_name_;
    }

    void set_client_name(const std::string &name)
    {
        client_name_ = name;
    }


private:
    int account_number_;
    std::string client_name_;
};


class bank_db
{
public:
    bool add_account(const bank_account &account);
    bool delete_account(int account_number);
    bank_account &find_account(int account_number);
    bank_account &find_account(const std::string& name);
    void merge_data_base(bank_db &db);

private:
    std::map<int, bank_account> accounts_;
};

















#endif