#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

Transaction::Transaction(std::string accNum, std::string type, double amount)
    : accountNumber(accNum), type(type), amount(amount), timestamp(std::time(nullptr)) {}

std::string Transaction::getAccountNumber() const {
    return accountNumber;
}

std::string Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getTimestamp() const {
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&timestamp));
    return std::string(buffer);
}

void Transaction::logTransaction() {
    std::ofstream file("transactions.log", std::ios::app);
    if (file.is_open()) {
        file << getTimestamp() << " - "
             << "Account: " << accountNumber << " - "
             << "Type: " << type << " - "
             << "Amount: $" << std::fixed << std::setprecision(2) << amount << "\n";
        file.close();
    }
}