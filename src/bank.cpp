#include "../include/bank.h"
#include "../include/utils.h"
#include <iostream>

int Bank::createCheckingAccount(const std::string& owner, double initialBalance, double limit, double fee) {
    int newID = Utils::generateRandomID(database);
    database[newID] = std::make_unique<checkingAccount>(owner, initialBalance, limit, fee);
    return newID;
}

int Bank::createSavingsAccount(const std::string& owner, double initialBalance, double interestRate) {
    int newID = Utils::generateRandomID(database);
    database[newID] = std::make_unique<savingsAccount>(owner, initialBalance, interestRate);
    return newID;
}

bool Bank::deposit(int id, double amount) {
    auto it = database.find(id);
    if (it != database.end()) {
        return it->second->deposit(amount);
    }
    return false;
}

WithdrawResult Bank::withdraw(int id, double amount) {
    auto it = database.find(id);
    if (it != database.end()) {
        return it->second->withdraw(amount);
    }
    return {false, false, "Account not found"};
}

void Bank::applyInterestToAll() {
    for (auto& pair : database) {
        if (savingsAccount* sa = dynamic_cast<savingsAccount*>(pair.second.get())) {
            sa->applyInterest();
        }
    }
}

void Bank::displayAllAccounts() const {
    for (const auto& pair : database) {
        std::cout << pair.first << " | ";
        pair.second->display();
    }
}

bool Bank::accountExists(int id) const {
    return database.find(id) != database.end();
}

account* Bank::getAccount(int id) {
    auto it = database.find(id);
    if (it != database.end()) {
        return it->second.get();
    }
    return nullptr;
}
