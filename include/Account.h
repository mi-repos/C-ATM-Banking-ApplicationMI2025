#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string accountNumber;
    std::string pin;
    double balance;
    std::string holderName;
    
public:
    Account();
    Account(std::string accNum, std::string pin, double balance, std::string holder);
    
    std::string getAccountNumber() const;
    std::string getPin() const;
    double getBalance() const;
    std::string getHolderName() const;
    
    void setPin(std::string newPin);
    void setBalance(double newBalance);
    
    bool withdraw(double amount);
    void deposit(double amount);
    bool changePin(std::string oldPin, std::string newPin);
};

#endif