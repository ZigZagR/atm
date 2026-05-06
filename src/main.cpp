#include <iostream>
#include <string>
#include <limits>
#include <ctime>
#include <cstdlib>

#include "../include/bank.h"
#include "../include/utils.h"

using namespace std;

void renderMenu();
int getIntInput();
double getDoubleInput();
string getStringInput();
bool processChoice(int choice, Bank& bank);

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    Bank myBank;
    bool running = true;

    printf("\033[2J\033[H");
    fflush(stdout);

    while (running) {
        renderMenu();
        int choice = getIntInput();
        running = processChoice(choice, myBank);
    }

    return 0;
}

void renderMenu() {
    cout << "========================\n";
    cout << "       BANK MENU        \n";
    cout << "========================\n";
    cout << "1. New Account\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Apply Interest (Savings)\n";
    cout << "5. List All Accounts\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}

int getIntInput() {
    int input;
    if (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

double getDoubleInput() {
    double input;
    if (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1.0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

string getStringInput() {
    string input;
    getline(cin, input);
    return input;
}

bool processChoice(int choice, Bank& bank) {
    switch (choice) {
        case 0:
            cout << "Exiting... Goodbye!\n";
            return false;

        case 1: {
            cout << "\nAccount Type:\n1. Checking\n2. Savings\nChoice: ";
            int type = getIntInput();
            if (type != 1 && type != 2) {
                cout << "ERROR: Invalid selection.\n";
                break;
            }

            cout << "Owner Name: ";
            string owner = getStringInput();
            if (owner.empty()) {
                cout << "ERROR: Name cannot be empty.\n";
                break;
            }

            cout << "Initial Balance: ";
            double balance = getDoubleInput();
            if (balance < 0) {
                cout << "ERROR: Balance cannot be negative.\n";
                break;
            }

            if (type == 1) {
                cout << "Overdraft Limit: ";
                double limit = getDoubleInput();
                int id = bank.createCheckingAccount(owner, balance, limit, 35.00);
                cout << "SUCCESS: Checking account created. ID: " << id << "\n";
            } else {
                cout << "Interest Rate (e.g. 0.05 for 5%): ";
                double rate = getDoubleInput();
                if (rate <= 0) {
                    cout << "ERROR: Rate must be positive.\n";
                    break;
                }
                int id = bank.createSavingsAccount(owner, balance, rate);
                cout << "SUCCESS: Savings account created. ID: " << id << "\n";
            }
            break;
        }

        case 2: {
            cout << "\nEnter Account ID: ";
            int id = getIntInput();
            if (!Utils::isValidLuhn(id)) {
                cout << "ERROR: Invalid ID format.\n";
                break;
            }

            cout << "Deposit Amount: ";
            double amount = getDoubleInput();
            if (bank.deposit(id, amount)) {
                cout << "SUCCESS: Deposited $" << amount << ".\n";
            } else {
                cout << "ERROR: Deposit failed (Account not found or invalid amount).\n";
            }
            break;
        }

        case 3: {
            cout << "\nEnter Account ID: ";
            int id = getIntInput();
            if (!Utils::isValidLuhn(id)) {
                cout << "ERROR: Invalid ID format.\n";
                break;
            }

            cout << "Withdrawal Amount: ";
            double amount = getDoubleInput();
            WithdrawResult result = bank.withdraw(id, amount);
            
            if (result.success) {
                cout << "SUCCESS: Withdrew $" << amount << ".\n";
                if (result.warning) cout << "NOTICE: " << result.message << "\n";
            } else {
                cout << "ERROR: " << result.message << "\n";
            }
            break;
        }

        case 4:
            bank.applyInterestToAll();
            cout << "\nSUCCESS: Interest applied to all savings accounts.\n";
            break;

        case 5:
            cout << "\n--- All Accounts ---\n";
            bank.displayAllAccounts();
            cout << "--------------------\n";
            break;

        default:
            cout << "ERROR: Unknown command.\n";
            break;
    }
    cout << "\n";
    return true;
}