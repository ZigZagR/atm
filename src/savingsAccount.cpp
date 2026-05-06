#include "savingsAccount.h"

savingsAccount::savingsAccount(std::string name, double initial, double rate) : account(name, initial) {
    if(rate < 0){
        std::cout << "ERROR: Interest rate cannot be negative.\n";
        interestRate = 0.0;
    }else{
        interestRate = rate;
    }
}

void savingsAccount::applyInterest() {
    balance *= 1 + interestRate;
}

void savingsAccount::display() const{
    std::cout << owner << " | Balance: $" << balance << " | Interest Rate: " << interestRate * 100 << "% per month.\n";
}