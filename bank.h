#ifndef BANK_H
#define BANK_H


#include "currency.h"

#include <bits/stdc++.h>


enum class AccountType {
    personal, organization
};

struct Transaction {
    std::string date;
    double amount;
    std::string currency_type;
    std::string description;
};

class BankAccount {
private:
    std::string accountHolder;
    std::string accountNumber;
    AccountType accountType;
    std::string lastTransactionDate;
    std::unique_ptr<Currency> balance;
    double dailyTransferredUSD;
    std::vector<Transaction> transactions;
    bool newDay();

public:
    BankAccount(std::string name, std::string number, AccountType type, std::unique_ptr<Currency> balance);
    void deposit(const Currency& amount, std::string description = "deposit");
    void withdraw(const Currency& amount, std::string description = "withdraw");
    void transfer(BankAccount& toAccount, const Currency& amount, std::string description = "transfer");
    const Currency& getBalance() const;
    void printStatement() const;
};

#endif