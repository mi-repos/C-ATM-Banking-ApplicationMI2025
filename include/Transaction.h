#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Transaction {
private:
    std::string accountNumber;
    std::string type;
    double amount;
    std::time_t timestamp;
    
public:
    Transaction(std::string accNum, std::string type, double amount);
    
    std::string getAccountNumber() const;
    std::string getType() const;
    double getAmount() const;
    std::string getTimestamp() const;
    
    void logTransaction();
};

#endif