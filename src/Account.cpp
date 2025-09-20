#include "Account.h"
#include <stdexcept>

Account::Account() : accountNumber(""), pin(""), balance(0.0), holderName("") {}

Account::Account(std::string accNum, std::string pin, double balance, std::string holder)
    : accountNumber(accNum), pin(pin), balance(balance), holderName(holder) {}

std::string Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getPin() const {
    return pin;
}

double Account::getBalance() const {
    return balance;
}

std::string Account::getHolderName() const {
    return holderName;
}

void Account::setPin(std::string newPin) {
    pin = newPin;
}

void Account::setBalance(double newBalance) {
    balance = newBalance;
}

bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Account::changePin(std::string oldPin, std::string newPin) {
    if (oldPin == pin) {
        pin = newPin;
        return true;
    }
    return false;
}