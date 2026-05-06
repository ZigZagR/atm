#include "account.h"

account::account(std::string name, double initial) {
    owner = name;
	if(initial < 0){
		std::cout << "Error: Initial balance cannot be negative.\n";
		balance = 0.0;
	} else {
		balance = initial;
	}

}

bool account::deposit(double amount) {
	if(amount <= 0){
		std::cout << "Error: Invalid amount. Need to be more then 0.\n";
		return false;
	}
	balance += amount;
	return true;
}

WithdrawResult account::withdraw(double amount) {
	if(amount <= balance){
		balance -= amount;
		return {true, false, ""};
	}
	return {false, true, "Insuficient funds."};
}

void account::display() const {
	std::cout << owner << " | Balance: $" << balance << "\n";
}

double account::getBalance() const {
	return balance;
}
