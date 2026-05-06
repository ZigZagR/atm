#ifndef BANK_H
#define BANK_H

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "account.h"
#include "savingsAccount.h"
#include "checkingAccount.h"

class Bank {
private:
    std::unordered_map<int, std::unique_ptr<account>> database;

public:
    Bank() = default;

    int createCheckingAccount(const std::string& owner, double initialBalance, double limit, double fee);
    int createSavingsAccount(const std::string& owner, double initialBalance, double interestRate);
    
    bool deposit(int id, double amount);
    WithdrawResult withdraw(int id, double amount);
    
    void applyInterestToAll();
    void displayAllAccounts() const;
    
    bool accountExists(int id) const;
    account* getAccount(int id);
};

#endif
