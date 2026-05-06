#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <limits>
#include <unordered_map>
#include <ctime>

#include "account.h"
#include "savingsAccount.h"
#include "checkingAccount.h"

using namespace std; 

void render();
int getInput();
double getAmount();
string getOwner();
bool handleInput(int choice, std::unordered_map<int, std::unique_ptr<account>>& database);

int main(){
        srand(time(NULL));
        std::unordered_map<int, std::unique_ptr<account>> database;
        bool running = true;

        printf("\033[2J\033[H");
        fflush(stdout); 

        do{
                render();
                int choice = getInput();
                running = handleInput(choice, database);
        }while(running);
}

int calculateLuhnCheckDigit(int base){
        int sum = 0;
        bool doubleDigit = true;
        int temp = base;

        while(temp > 0){
                int digit = temp % 10;

                if(doubleDigit){
                        digit *= 2;
                        if(digit > 9) digit - 9;
                }
                sum += digit;
                doubleDigit = !doubleDigit;
                temp /= 10;
        }
        return (10 - (sum % 10) % 10);
}

int generateRandomID(const std::unordered_map<int, std::unique_ptr<account>>& database){
        int newID;
        bool unique = false;

        while(!unique){
                int base = rand() % 90000 + 10000;

                int luhnDigit = calculateLuhnCheckDigit(base);
                newID = (base * 10) + luhnDigit;

                if(database.find(newID) == database.end()){
                        unique = true;
                }
        }

        return newID;
}

bool isValidLuhn(int id){
        int sum = 0;
        bool doubleDigit = false;
        int temp = id;

        while(temp > 0){
                int digit = temp % 10;

                if(doubleDigit){
                        digit *= 2;
                        if(digit > 9) digit - 9;
                }
                sum += digit;
                doubleDigit = !doubleDigit;
                temp /= 10;
        }
        return (sum % 10 == 0);
}

void render(){
        cout << "BANK MENU\n";
        cout << "1. New Account.\n";
        cout << "2. Deposit.\n";
        cout << "3. Withdraw.\n";
        cout << "4. Apply Interest (savings only).\n";
        cout << "5. List All accounts.\n";
        cout << "0. Exit\n";
}

int getInput(){
        int choice;

        if(!(cin >> choice)){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "ERROR: Invalid input.\n";
                cout << "\n";
                return -1;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
}

double getAmount(){
        double amount;

        if(!(cin >> amount)){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "ERROR: Invalid input.\n";
                cout << "\n";
                return -1;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return amount;
}

string getOwner(){
        std::string owner;

        getline(cin, owner);
        return owner;

}

bool handleInput(int choice, std::unordered_map<int, std::unique_ptr<account>>& database){
        if(choice == -1){
                return false;
        }else if(choice == 0){
                return false;
                
        }else if(choice == 1){
                cout << "\n";
                cout << "Account type: \n";
                cout << "1. Checking Account.\n";
                cout << "2. Savings Account.\n";
                int choice = getInput();
                
                if(choice != 1 && choice != 2){
                        cout << "ERROR: Invalid Input\n"; 
                        return true;
                }        

                cout << "Input account owner: ";
                std::string owner;
                owner = getOwner();

                cout << "Input initial balance: ";
                double initialBalance;
                initialBalance = getAmount(); 
                

                if(initialBalance < 0){
                        cout << "ERROR: Initial balance can't be lower then 0.\n";
                        cout << "\n";
                        return true;
                }

                if(owner.empty()){
                        cout << "ERROR: Name is empty.\n";
                        cout << "\n";
                        return true;
                }

                if(choice == 1){
 
                        cout << "Input overdraft limit: ";
                        double limit = getAmount();
                        double standardFee = 35.00;
                        int newID = generateRandomID(database);
                        database[newID] = make_unique<checkingAccount>(owner, initialBalance, limit, standardFee);
                        cout << "Account created successfully. Your ID is: " << newID << "\n";

                }else if(choice == 2){
                        cout << "Interest rate(in decimal): ";
                        double interestRate = getAmount();
                        if(interestRate <= 0){
                                cout << "ERROR: rate must be higher then 0.\n";
                                cout << "\n";
                                return true;
                        }
                        int newID = generateRandomID(database);
                        database[newID] = make_unique<savingsAccount>(owner, initialBalance, interestRate);
                        cout << "Account created successfully. Your ID is: " << newID << "\n";
                }
                
        }else if(choice == 2){
                cout << "\n";
                cout << "Enter account ID: ";
                int id = getInput(); 

                if(!isValidLuhn(id)){
                        cout << "ERROR: Invalid Account ID format.\n";
                        return true;
                }
                
                auto it = database.find(id);
                if(it == database.end()){
                        cout << "ERROR: Account ID " << id << " not found.";
                        return true;
                }

                double amount;
                cout << "Input deposit amount: R$";
                amount = getAmount();

                if(it->second->deposit(amount)){
                        cout << "Deposited: " << amount << " successfully.\n";
                }else{
                        cout << "ERROR: Deposit failed.\n";
                }
                cout << "\n";

        }else if(choice == 3){
                cout << "\n";
                cout << "Enter account ID: ";
                int id = getInput();

                if(!isValidLuhn(id)){
                        cout << "ERROR: Invalid Account ID format.\n";
                        return true;
                }

                auto it = database.find(id);
                if(it == database.end()){
                        cout << "ERROR: Account ID " << id << " not found.";
                        return true;
                }
                double amount;
                cout << "Input withdraw amount: R$";
                amount = getAmount();

                auto result = it->second->withdraw(amount);

                if(result.success){
                        cout << "Withdraw: " << amount << " successfully.\n";
                        if(result.warning){
                                cout << result.message << "\n";
                        }
                }else{
                        cout << "ERROR: " << result.message << "\n";
                }
                cout << "\n";

        }else if(choice == 4){
                for(auto& pair : database){
                        if(savingsAccount* sa = dynamic_cast<savingsAccount*>(pair.second.get())){
                                sa->applyInterest();
                        }
                }
                cout << "\n";
                cout << "Interest applied.\n";
                cout << "\n";
        }else if(choice == 5){
                cout << "\n";
                for(auto& pair : database){
                        cout << pair.first << " | ";
                        pair.second->display();
                }
                cout << "\n";
        }
        return true;
}