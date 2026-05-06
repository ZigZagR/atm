#include "checkingAccount.h"

checkingAccount::checkingAccount(std::string name, double initial, double limit, double fee) : account(name, initial){
    overdraftLimit = limit;
    overdraftFee = fee;
}

WithdrawResult checkingAccount::withdraw(double amount){
    if(amount <= 0) return {false, true, "Amount can't be lower then 0."};
            
    if(balance - amount >= -overdraftLimit){
        balance -= amount;

        if(balance < 0){
            balance -= overdraftFee;
            return {true, true, "Overdraft used. Fee applied."};
        }
        return {true, false, ""};
    }
    return {false, true, "Overdraft limit exceed."};
}

void checkingAccount::display() const {
	std::cout << owner << " | Balance: $" << balance << " | Limit: $" << overdraftLimit << "\n";
}

bool checkingAccount::inOverdraft() const{
    return balance < 0;
}

