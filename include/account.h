#pragma once

#include <string>
#include <iostream>

struct WithdrawResult{
    bool success;
    bool warning;
    std::string message;
};

class account {
protected:
    std::string owner;
    double balance;
public:
    account(std::string name, double initial);

    virtual ~account() = default;

    virtual bool deposit(double amount);
    virtual WithdrawResult withdraw(double amount);
    virtual void display() const;
    double getBalance() const;
};