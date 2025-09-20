#include "Bank.h"
#include "Account.h"
#include <fstream>
#include <sstream>
#include <iostream>

Bank::Bank(std::string filename) : dataFile(filename) {
    loadAccounts();
}

Bank::~Bank() {
    saveAccounts();
}

void Bank::loadAccounts() {
    std::ifstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open data file. Starting with empty accounts." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string accNum, pin, holder;
        double balance;
        
        if (std::getline(ss, accNum, ',') &&
            std::getline(ss, pin, ',') &&
            ss >> balance &&
            ss.ignore() &&
            std::getline(ss, holder)) {
            
            accounts.push_back(Account(accNum, pin, balance, holder));
        }
    }
    
    file.close();
}

void Bank::saveAccounts() {
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not save accounts to file." << std::endl;
        return;
    }
    
    for (const auto& account : accounts) {
        file << account.getAccountNumber() << ","
             << account.getPin() << ","
             << account.getBalance() << ","
             << account.getHolderName() << "\n";
    }
    
    file.close();
}

Account* Bank::authenticate(std::string accountNumber, std::string pin) {
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accountNumber && account.getPin() == pin) {
            return &account;
        }
    }
    return nullptr;
}

Account* Bank::getAccount(std::string accountNumber) {
    for (auto& account : accounts) {
        if (account.getAccountNumber() == accountNumber) {
            return &account;
        }
    }
    return nullptr;
}

bool Bank::updateAccount(Account& updatedAccount) {
    for (auto& account : accounts) {
        if (account.getAccountNumber() == updatedAccount.getAccountNumber()) {
            account = updatedAccount;
            saveAccounts();
            return true;
        }
    }
    return false;
}