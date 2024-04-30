#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Account {
public:
    int accountNumber;
    string name;
    int balance;

    Account(int accNum, const std::string& accName, int initialBalance)
        : accountNumber(accNum), name(accName), balance(initialBalance) {}
};

class Transaction {
public:
    int value;
    int fromAccount;
    int toAccount;

    Transaction(int val, int fromAcc, int toAcc)
        : value(val), fromAccount(fromAcc), toAccount(toAcc) {}
};

class BankSystem {
private:
    vector<Account> accounts;
    vector<Transaction> transactions;

public:
    void createAccount() {
        int accountNumber, balance;
        string name;
        cout << "Enter account number: ";
        cin >> accountNumber;
        cin.ignore();  // Ignore trailing newline
        cout << "Enter account holder's name: ";
        getline(std::cin, name);
        cout << "Enter initial balance: ";
        cin >> balance;
        accounts.emplace_back(accountNumber, name, balance);
        cout << "Account " << accountNumber << " created for " << name << " with balance $" << balance << ".\n";
    }

    void deleteAccount() {
        int accountNumber;
        cout << "Enter account number to delete: ";
        cin >> accountNumber;
        auto it = remove_if(accounts.begin(), accounts.end(), [accountNumber](const Account& acc) {
            return acc.accountNumber == accountNumber;
        });
        if (it != accounts.end()) {
            accounts.erase(it, accounts.end());
            cout << "Account " << accountNumber << " has been deleted.\n";
        } else {
            cout << "Account does not exist.\n";
        }
    }

    void showBalance() {
        int accountNumber;
        cout << "Enter account number to view balance: ";
        cin >> accountNumber;
        auto it = find_if(accounts.begin(), accounts.end(), [accountNumber](const Account& acc) {
            return acc.accountNumber == accountNumber;
        });
        if (it != accounts.end()) {
            cout << "The balance for account " << accountNumber << " is $" << it->balance << ".\n";
        } else {
            cout << "Account does not exist.\n";
        }
    }

    void transaction() {
        int fromAcc, toAcc, amount;
        cout << "Enter from account number: ";
        cin >> fromAcc;
        cout << "Enter to account number: ";
        cin >> toAcc;
        cout << "Enter transfer amount: ";
        cin >> amount;
        auto fromIt = find_if(accounts.begin(), accounts.end(), [fromAcc](const Account& acc) {
            return acc.accountNumber == fromAcc;
        });
        auto toIt = find_if(accounts.begin(), accounts.end(), [toAcc](const Account& acc) {
            return acc.accountNumber == toAcc;
        });
        if (fromIt != accounts.end() && toIt != accounts.end()) {
            if (fromIt->balance >= amount) {
                fromIt->balance -= amount;
                toIt->balance += amount;
                transactions.emplace_back(amount, fromAcc, toAcc);
                cout << "Transaction successful: $" << amount << " transferred from account " << fromAcc << " to account " << toAcc << ".\n";
            } else {
                cout << "Insufficient balance.\n";
            }
        } else {
            cout << "One or both accounts do not exist.\n";
        }
    }

    void showAllBalances() {
        for (const auto& account : accounts) {
            cout << "Account " << account.accountNumber << ", Name: " << account.name << ", Balance: $" << account.balance << "\n";
        }
    }

    void showAllTransactions() {
        for (const auto& transaction : transactions) {
            cout << "$" << transaction.value << " from Account " << transaction.fromAccount << " to Account " << transaction.toAccount << "\n";
        }
    }
};

int main() {
    BankSystem bank;
    char option;
    do {
        cout << "Choose an option:\n";
        cout << "1. Create Account\n";
        cout << "2. Delete Account\n";
        cout << "3. Show Balance\n";
        cout << "4. Make Transaction\n";
        cout << "5. Show All Balances\n";
        cout << "6. Show All Transactions\n";
        cout << "7. Exit\n";
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
            case '1':
                bank.createAccount();
                break;
            case '2':
                bank.deleteAccount();
                break;
            case '3':
                bank.showBalance();
                break;
            case '4':
                bank.transaction();
                break;
            case '5':
                bank.showAllBalances();
                break;
            case '6':
                bank.showAllTransactions();
                break;
            case '7':
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (option != '7');
    return 0;
}
