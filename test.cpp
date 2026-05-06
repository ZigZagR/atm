#include <iostream>
#include <cassert>
#include "account.h"
#include "savingsAccount.h"

using namespace std;

void testAccount() {
    cout << "Testing basic account logic...\n";
    
    account acc("Zig", 100.0);
    
    assert(acc.getBalance() == 100.0);

    bool depResult = acc.deposit(50.0);
    assert(depResult == true);           // The method should return true
    assert(acc.getBalance() == 150.0);   // The balance should increase by 50

    bool withResult = acc.withdraw(30.0);
    assert(withResult == true);
    assert(acc.getBalance() == 120.0);

    bool badDepResult = acc.deposit(-10.0);
    assert(badDepResult == false);       // The method should refuse the deposit
    assert(acc.getBalance() == 120.0);   // Balance should remain unchanged!

    bool badWithResult = acc.withdraw(500.0);
    assert(badWithResult == false);
    assert(acc.getBalance() == 120.0);   // Balance should remain unchanged!
}

void testSavingsAccount() {
    cout << "Testing savings account logic...\n";
    
    savingsAccount sacc("Duda", 1000.0, 0.05);
    assert(sacc.getBalance() == 1000.0);

    sacc.applyInterest();

    assert(sacc.getBalance() == 1050.0);
}

void testVulnerabilities() {
    cout << "Trying to break the bank...\n";

    account negativeStart("Hacker", -5000.0);
    
    assert(negativeStart.getBalance() == 0.0);

    savingsAccount badBank("Victim", 1000.0, -0.99); // -99% interest!
    badBank.applyInterest();
    
    assert(badBank.getBalance() >= 1000.0); 
}

int main() {
    cout << "\n=== STARTING AUTOMATED TESTS ===\n\n";
    
    testAccount();
    
    cout << "\n";
    testSavingsAccount();

    cout << "\n";
    testVulnerabilities();
    
    cout << "\n=== ALL TESTS PASSED SUCCESSFULLY! ===\n\n";
    
    return 0;
}
