#include "bank.h"

#include <bits/stdc++.h>

bool BankAccount::newDay() {
    std::time_t now = time(0);
    std::tm* nowTm = localtime(&now);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", nowTm);
    if (lastTransactionDate != today) {
        lastTransactionDate = today;
        dailyTransferredUSD = 0;
        return true;
    }
    return false;
}

BankAccount::BankAccount(std::string name, std::string number, AccountType type, std::unique_ptr<Currency> balance)
    : accountHolder(name), accountNumber(number), accountType(type), balance(std::move(balance)), dailyTransferredUSD(0) {
    std::time_t now = time(0);
    std::tm* now_tm = localtime(&now);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", now_tm);
    lastTransactionDate = today;
}

void BankAccount::deposit(const Currency& amount, std::string description) {
    if (amount.getValue() <= 0) {
        std::cout << "The deposit amount must be positive.\n";
        return;
    }
    double amount_usd = amount.convertTo("USD");
    *balance = *(*balance + amount);
    transactions.push_back({lastTransactionDate, amount.getValue(), amount.getType(), description});
    std::cout << "Deposited " << amount << ". New balance: " << *balance << "\n";
}

void BankAccount::withdraw(const Currency& amount, std::string description) {
    if (amount.getValue() <= 0) {
        std::cout << "Error: The withdrawal amount must be positive.\n";
        return;
    }
    double amount_usd = amount.convertTo("USD");
    if (balance->convertTo("USD") < amount_usd) {
        std::cout << "Error: Insufficient balance.\n";
        return;
    }
    *balance = *(*balance - amount);
    transactions.push_back({lastTransactionDate, -amount.getValue(), amount.getType(), description});
    std::cout << "Withdrawn " << amount << ". New balance: " << *balance << "\n";
}

void BankAccount::transfer(BankAccount& toAccount, const Currency& amount, std::string description) {
    newDay();
    double amount_usd = amount.convertTo("USD");
    double maxDailyTransfer = (accountType == AccountType::personal) ? 1000 : 10000;
    if (dailyTransferredUSD + amount_usd > maxDailyTransfer) {
        std::cout << "Error: Daily transfer limit exceeded.\n";
        return;
    }
    if (balance->convertTo("USD") < amount_usd) {
        std::cout << "Error: Insufficient balance.\n";
        return;
    }
    *balance = *(*balance - amount);
    *toAccount.balance = *(*toAccount.balance + amount);
    dailyTransferredUSD += amount_usd;
    transactions.push_back({lastTransactionDate, -amount.getValue(), amount.getType(), "To Account " + toAccount.accountNumber + ": " + description});
    toAccount.transactions.push_back({lastTransactionDate, amount.getValue(), amount.getType(), "From Account " + accountNumber + ": " + description});
    std::cout << "Transferred " << amount << " to Account " << toAccount.accountNumber << ".\n";
}

const Currency& BankAccount::getBalance() const {
    return *balance;
}

void BankAccount::printStatement() const {
    std::cout << "Account Summary for " << accountHolder << "\n";
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Current Balance: " << *balance << "\n";
    std::cout << "Account Type: " << (accountType == AccountType::personal ? "Personal" : "Organization") << "\n";
    std::cout << "--------------------------------\n";
    std::cout << "Transaction History:\n";
    for (const auto& t : transactions) {
        std::cout << t.date << " | ";
        if (t.amount >= 0) std::cout << "+";
        std::cout << t.amount << " " << t.currency_type << " | " << t.description << "\n";
    }
    std::cout << "--------------------------------\n";
}