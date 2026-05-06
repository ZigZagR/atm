#include <iostream>
#include <cassert>
#include "../include/account.h"
#include "../include/savingsAccount.h"
#include "../include/bank.h"

using namespace std;

void testAccount() {
    cout << "Testing basic account logic...\n";
    
    account acc("Zig", 100.0);
    
    assert(acc.getBalance() == 100.0);

    bool depResult = acc.deposit(50.0);
    assert(depResult == true);
    assert(acc.getBalance() == 150.0);

    WithdrawResult withResult = acc.withdraw(30.0);
    assert(withResult.success == true);
    assert(acc.getBalance() == 120.0);

    bool badDepResult = acc.deposit(-10.0);
    assert(badDepResult == false);
    assert(acc.getBalance() == 120.0);

    WithdrawResult badWithResult = acc.withdraw(500.0);
    assert(badWithResult.success == false);
    assert(acc.getBalance() == 120.0);
}

void testSavingsAccount() {
    cout << "Testing savings account logic...\n";
    
    savingsAccount sacc("Duda", 1000.0, 0.05);
    assert(sacc.getBalance() == 1000.0);

    sacc.applyInterest();

    assert(sacc.getBalance() == 1050.0);
}

void testBankLogic() {
    cout << "Testing Bank manager logic...\n";
    Bank myBank;
    
    int id1 = myBank.createCheckingAccount("Owner1", 1000.0, 500.0, 35.0);
    int id2 = myBank.createSavingsAccount("Owner2", 2000.0, 0.10);
    
    assert(myBank.accountExists(id1));
    assert(myBank.accountExists(id2));
    
    assert(myBank.deposit(id1, 500.0));
    assert(myBank.getAccount(id1)->getBalance() == 1500.0);
    
    WithdrawResult res = myBank.withdraw(id2, 100.0);
    assert(res.success == true);
    assert(myBank.getAccount(id2)->getBalance() == 1900.0);
}

int main() {
    cout << "\n=== STARTING AUTOMATED TESTS ===\n\n";
    
    testAccount();
    cout << "\n";
    testSavingsAccount();
    cout << "\n";
    testBankLogic();
    
    cout << "\n=== ALL TESTS PASSED SUCCESSFULLY! ===\n\n";
    
    return 0;
}
