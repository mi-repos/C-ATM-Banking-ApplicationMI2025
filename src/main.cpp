#include "Bank.h"
#include "ATM.h"
#include <iostream>

int main() {
    // Initialize the bank with data file
    Bank bank("data/accounts.dat");
    
    // Create and run the ATM
    ATM atm(&bank);
    atm.run();
    
    return 0;
}