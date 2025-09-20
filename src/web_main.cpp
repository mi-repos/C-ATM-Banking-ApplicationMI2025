#include "Bank.h"
#include "ATM.h"
#include <iostream>
#include <emscripten.h>
#include <sstream>
#include <iomanip>  // Added for std::fixed

Bank* bank = nullptr;

// Custom setprecision implementation for Emscripten
namespace std_fix {
    template<typename T>
    std::string setprecision(T value, int precision) {
        std::stringstream ss;
        ss << std::fixed;
        ss.precision(precision);
        ss << value;
        return ss.str();
    }
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void initATM() {
        bank = new Bank("accounts.dat");
    }
    
    EMSCRIPTEN_KEEPALIVE
    const char* runATM(const char* input) {
        static std::string output;
        std::stringstream response;
        
        std::string cmd(input);
        
        if (cmd == "start") {
            response << "Welcome to Web ATM! Please enter your account number:";
        } 
        else if (cmd.find("auth:") == 0) {
            size_t sep = cmd.find(':', 5);
            if (sep != std::string::npos) {
                std::string accNum = cmd.substr(5, sep-5);
                std::string pin = cmd.substr(sep+1);
                
                Account* account = bank->authenticate(accNum, pin);
                if (account) {
                    response << "Welcome, " << account->getHolderName() << "! Options: 1-Balance, 2-Withdraw, 3-Deposit, 4-Change PIN, 5-Exit";
                } else {
                    response << "Authentication failed. Please try again.";
                }
            }
        }
        else if (cmd.find("balance:") == 0) {
            std::string accNum = cmd.substr(8);
            Account* account = bank->getAccount(accNum);
            if (account) {
                response << "Your balance is: $" << std_fix::setprecision(account->getBalance(), 2);
            } else {
                response << "Account not found.";
            }
        }
        else if (cmd.find("withdraw:") == 0) {
            size_t sep = cmd.find(':', 9);
            if (sep != std::string::npos) {
                std::string accNum = cmd.substr(9, sep-9);
                double amount = std::stod(cmd.substr(sep+1));
                
                Account* account = bank->getAccount(accNum);
                if (account && account->withdraw(amount)) {
                    bank->updateAccount(*account);
                    response << "Withdrawal successful. New balance: $" << std_fix::setprecision(account->getBalance(), 2);
                } else {
                    response << "Withdrawal failed. Insufficient funds or invalid amount.";
                }
            }
        }
        else if (cmd.find("deposit:") == 0) {
            size_t sep = cmd.find(':', 8);
            if (sep != std::string::npos) {
                std::string accNum = cmd.substr(8, sep-8);
                double amount = std::stod(cmd.substr(sep+1));
                
                Account* account = bank->getAccount(accNum);
                if (account) {
                    account->deposit(amount);
                    bank->updateAccount(*account);
                    response << "Deposit successful. New balance: $" << std_fix::setprecision(account->getBalance(), 2);
                } else {
                    response << "Account not found.";
                }
            }
        }
        else if (cmd.find("changepin:") == 0) {
            size_t sep1 = cmd.find(':', 10);
            size_t sep2 = cmd.find(':', sep1+1);
            if (sep1 != std::string::npos && sep2 != std::string::npos) {
                std::string accNum = cmd.substr(10, sep1-10);
                std::string oldPin = cmd.substr(sep1+1, sep2-sep1-1);
                std::string newPin = cmd.substr(sep2+1);
                
                Account* account = bank->getAccount(accNum);
                if (account && account->changePin(oldPin, newPin)) {
                    bank->updateAccount(*account);
                    response << "PIN changed successfully.";
                } else {
                    response << "PIN change failed. Please check your current PIN.";
                }
            }
        }
        else {
            response << "Unknown command: " << cmd;
        }
        
        output = response.str();
        return output.c_str();
    }
    
    EMSCRIPTEN_KEEPALIVE
    void cleanupATM() {
        delete bank;
        bank = nullptr;
    }
}