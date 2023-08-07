#include <stdexcept>
#include "bank.h"


bool bank_db::add_account(const bank_account &account)
{
    auto ret = accounts_.emplace(account.get_account_number(), account);
    return ret.second;
}

bool bank_db::delete_account(int account_number)
{
    accounts_.erase(account_number);


    return false;
}

bank_account &bank_db::find_account(int account_number)
{
    if (auto it = accounts_.find(account_number); it != accounts_.end())
    {
        return it->second;
    }
    else
        throw std::out_of_range("No account with that number.");
}

bank_account &bank_db::find_account(const std::string& name)
{
    for (auto &[number, account] : accounts_)
    {
        if (account.get_client_name() == name)
            return account;
    }
    throw std::out_of_range("No account with that name.");
}

void bank_db::merge_data_base(bank_db &db)
{
    accounts_.merge(db.accounts_);
    db.accounts_.clear();
}