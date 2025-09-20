#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include "Account.h"

class Bank {
private:
    std::vector<Account> accounts;
    std::string dataFile;
    
    void loadAccounts();
    void saveAccounts();
    
public:
    Bank(std::string filename);
    ~Bank();
    
    Account* authenticate(std::string accountNumber, std::string pin);
    Account* getAccount(std::string accountNumber);
    bool updateAccount(Account& updatedAccount);
};

#endif