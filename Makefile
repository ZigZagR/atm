all:
	g++ main.cpp account.cpp savingsAccount.cpp checkingAccount.cpp -o bank
test:
	g++ test.cpp account.cpp savingsAccount.cpp checkingAccount.cpp -o test_bank