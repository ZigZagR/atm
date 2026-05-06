#pragma once

#include "account.h"
#include <iostream>

class checkingAccount : public account {
private:
    double overdraftLimit;
    double overdraftFee;
public:
    checkingAccount(std::string name, double initial, double limit, double fee);

    WithdrawResult withdraw(double amount) override;

    void display() const override;

    bool inOverdraft() const;
};
        