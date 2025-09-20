#ifndef ATM_H
#define ATM_H

#include "Bank.h"
#include <string>

class ATM {
private:
    Bank* bank;
    Account* currentAccount;
    
    void displayMainMenu();
    void checkBalance();
    void withdrawCash();
    void depositCash();
    void changePin();
    void exitATM();
    
public:
    ATM(Bank* bank);
    void run();
};

#endif