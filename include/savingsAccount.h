#pragma once

#include <string>
#include <iostream>

#include "account.h"

class savingsAccount : public account {
private:
    double interestRate;  // e.g. 0.05 = 5%
public:
    savingsAccount(std::string name, double initial, double rate);
    void applyInterest();      // adds balance * rate
    void display() const override;
};