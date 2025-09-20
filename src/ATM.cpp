#include "ATM.h"
#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <limits>

ATM::ATM(Bank* bank) : bank(bank), currentAccount(nullptr) {}

void ATM::run() {
    std::string accountNumber, pin;
    
    std::cout << "===================================\n";
    std::cout << "      WELCOME TO THE ATM SYSTEM    \n";
    std::cout << "===================================\n\n";
    
    std::cout << "Please enter your account number: ";
    std::cin >> accountNumber;
    
    std::cout << "Enter your PIN: ";
    std::cin >> pin;
    
    currentAccount = bank->authenticate(accountNumber, pin);
    
    if (currentAccount) {
        std::cout << "\nAuthentication successful!\n";
        std::cout << "Welcome, " << currentAccount->getHolderName() << "!\n\n";
        displayMainMenu();
    } else {
        std::cout << "\nAuthentication failed. Invalid account number or PIN.\n";
    }
}

void ATM::displayMainMenu() {
    int choice;
    
    do {
        std::cout << "\n===================================\n";
        std::cout << "             MAIN MENU             \n";
        std::cout << "===================================\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Withdraw Cash\n";
        std::cout << "3. Deposit Cash\n";
        std::cout << "4. Change PIN\n";
        std::cout << "5. Exit\n";
        std::cout << "===================================\n";
        std::cout << "Please enter your choice (1-5): ";
        
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                withdrawCash();
                break;
            case 3:
                depositCash();
                break;
            case 4:
                changePin();
                break;
            case 5:
                exitATM();
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void ATM::checkBalance() {
    std::cout << "\n===================================\n";
    std::cout << "          ACCOUNT BALANCE          \n";
    std::cout << "===================================\n";
    std::cout << "Your current balance is: $" 
              << std::fixed << std::setprecision(2) 
              << currentAccount->getBalance() << "\n";
}

void ATM::withdrawCash() {
    double amount;
    std::cout << "\n===================================\n";
    std::cout << "            WITHDRAW CASH          \n";
    std::cout << "===================================\n";
    std::cout << "Enter amount to withdraw: $";
    std::cin >> amount;
    
    if (amount <= 0) {
        std::cout << "Invalid amount. Please enter a positive value.\n";
        return;
    }
    
    if (currentAccount->withdraw(amount)) {
        bank->updateAccount(*currentAccount);
        Transaction transaction(currentAccount->getAccountNumber(), "WITHDRAWAL", amount);
        transaction.logTransaction();
        std::cout << "Please take your cash.\n";
        std::cout << "New balance: $" << std::fixed << std::setprecision(2) 
                  << currentAccount->getBalance() << "\n";
    } else {
        std::cout << "Insufficient funds or invalid amount.\n";
    }
}

void ATM::depositCash() {
    double amount;
    std::cout << "\n===================================\n";
    std::cout << "            DEPOSIT CASH           \n";
    std::cout << "===================================\n";
    std::cout << "Enter amount to deposit: $";
    std::cin >> amount;
    
    if (amount <= 0) {
        std::cout << "Invalid amount. Please enter a positive value.\n";
        return;
    }
    
    currentAccount->deposit(amount);
    bank->updateAccount(*currentAccount);
    Transaction transaction(currentAccount->getAccountNumber(), "DEPOSIT", amount);
    transaction.logTransaction();
    std::cout << "Deposit successful.\n";
    std::cout << "New balance: $" << std::fixed << std::setprecision(2) 
              << currentAccount->getBalance() << "\n";
}

void ATM::changePin() {
    std::string oldPin, newPin;
    std::cout << "\n===================================\n";
    std::cout << "            CHANGE PIN            \n";
    std::cout << "===================================\n";
    std::cout << "Enter your current PIN: ";
    std::cin >> oldPin;
    std::cout << "Enter your new PIN: ";
    std::cin >> newPin;
    
    if (currentAccount->changePin(oldPin, newPin)) {
        bank->updateAccount(*currentAccount);
        std::cout << "PIN changed successfully.\n";
    } else {
        std::cout << "Failed to change PIN. Please check your current PIN.\n";
    }
}

void ATM::exitATM() {
    currentAccount = nullptr;
    std::cout << "\n===================================\n";
    std::cout << "  Thank you for using our ATM.     \n";
    std::cout << "        Have a nice day!           \n";
    std::cout << "===================================\n";
}