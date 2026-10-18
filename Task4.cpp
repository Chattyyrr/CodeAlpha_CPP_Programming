/*
Internship Task 4: Banking System
- Design classes for Customer, Account and Transaction with necessary attributes.
- Implement functions to create and manage customers and accounts.
- Include features for deposits, withdrawals and fund transfers.
- Store transaction history and allow users to view recent transactions.
- Display account information like balance and transaction details to customers.
*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

std::string getCurrentTime() {
    time_t now = time(0);
    char *dt = ctime(&now);
    std::string s(dt);
    s.pop_back();
    return s;
}

class Transaction {
public:
    std::string type;
    double amount;
    std::string time;

    Transaction(std::string tp, double amt)
        : type(tp), amount(amt), time(getCurrentTime())
    {}

    void display() const {
        std::cout << std::left << std::setw(12) << type
                               << std::setw(10) << amount
                               << std::setw(25) << time
                                                << '\n';
    }
};

class Account {
public:
    std::string number;
    std::string customerId;
    std::string type;
    double balance;
    std::vector<Transaction> transactions;

    Account(std::string n, std::string cid, std::string tp, double bal)
        : number(n), customerId(cid), type(tp), balance(bal)
    {
        if (bal > 0.0) {
            transactions.emplace_back("Deposit", bal);
        }
    }

    bool deposit(double amount) {
        if (amount <= 0)
            return false;
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance)
            return false;
        balance -= amount;
        transactions.emplace_back("Withdraw", amount);
        return true;
    }

    bool transfer(Account &to, double amount) {
        if (amount <= 0 || amount > balance || number == to.number)
            return false;
        balance -= amount;
        to.balance += amount;
        to.transactions.emplace_back("Transfer Received", amount);
        transactions.emplace_back("Transfer sent", amount);
        return true;
    }

    void displayTransactions(int count) const {
        count = (count < transactions.size()) ? count : transactions.size();

        std::cout << "--- Last " << count << "transactions for " << number << " ---\n";
        std::cout << std::left << std::setw(12) << "Type"
                               << std::setw(10) << "Amount"
                               << std::setw(25) << "Time"
                                                << '\n';
        std::cout << std::string(46, '-') << '\n';

        if (count == 0) {
            std::cout << "No transactions.\n";
        } else {
            int index = transactions.size() - 1;
            for (int i = 0; i < count; ++i) {
                transactions[index--].display();
            }
        }
    }

    void display() const {
        std::cout << "--- Info for Account Number: " << number << " ---\n";
        std::cout << "Account number: " << number << '\n';
        std::cout << "Customer ID: " << customerId << '\n';
        std::cout << "Type: " << type << '\n';
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << '\n';
    }
};

class Customer {
public:
    std::string id;
    std::string name;
    std::vector<std::string> accountNumbers;

    Customer(std::string i, std::string n)
        : id(i), name(n)
    {}

    void display() const {
        std::cout << "\n--- Information for Customer ID: " << id << " ---\n";
        std::cout << "Name: " << name << '\n';
        std::cout << "Accounts: ";
        for (const std::string& accountNumber : accountNumbers) {
            std::cout << accountNumber << ' ';
        }
        std::cout << '\n';
    }
};

class BankingSystem {
    std::vector<Customer> customers;
    std::vector<Account> accounts;
    int custCounter = 1001;
    int accCounter = 50001;

public:
    Customer* findCustomer(const std::string& id) {
        for (Customer& customer : customers) {
            if (customer.id == id)
                return &customer;
        }
        return nullptr;
    }

    Account* findAccount(const std::string& number) {
        for (Account& account : accounts) {
            if (account.number == number)
                return &account;
        }
        return nullptr;
    }

    void createCustomer() {
        std::string name;
        
        std::cout << "Enter name: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        if (name.empty()) {
            std::cout << "No name entered.\n";
            return;
        }

        std::string id = "C" + std::to_string(custCounter++);
        customers.emplace_back(id, name);
        
        std::cout << "Customer created with ID: " << id << '\n';
    }

    void createAccount() {
        std::string custId, type;
        double balance;

        std::cout << "Enter customer ID: ";
        std::cin >> custId;
        
        if (!findCustomer(custId)) {
            std::cout << "No customer registered with specified ID.\n";
            return;
        }

        std::cout << "Enter account type: ";
        std::cin.ignore();
        std::getline(std::cin, type);

        std::cout << "Enter initial balance: ";
        std::cin >> balance;

        std::string number = "ACC" + std::to_string(accCounter++);
        accounts.emplace_back(number, custId, type, balance);
        findCustomer(custId)->accountNumbers.push_back(number);
        
        std::cout << "Account created with number: " << number << '\n';
    }

    Account* getAccount(
        const std::string &promptMsg = "Enter account number: ",
        const std::string &failureMsg = "No account found with specified number."
    ) {
        std::string number;
        std::cout << promptMsg;
        std::cin >> number;

        Account *account = findAccount(number);

        if (!account) {
            std::cout << failureMsg << '\n';
        }

        return account;
    }

    void depositOrWithdraw(bool deposit) {
        Account *account = getAccount();
        if (!account)
            return;

        double amount;
        std::cout << "Enter amount to be " << (deposit ? "deposited: " : "Withdrawn: ");
        std::cin >> amount;

        if ((deposit && account->deposit(amount)) ||
            (!deposit && account->withdraw(amount)))
        {
            std::cout << "Transaction successful, new balance: $"
                      << std::fixed << std::setprecision(2) << account->balance << '\n';
        } else {
            std::cout << "Transaction failed; invalid amount.\n";
        }
    }

    void deposit() {
        depositOrWithdraw(true);
    }
    
    void withdraw() {
        depositOrWithdraw(false);
    }

    void transfer() {
        std::cout << "--- Sender ---\n";

        Account *from = getAccount();
        if (!from)
            return;

        std::cout << "--- Recipient ---\n";

        Account *to = getAccount();
        if (!to)
            return;

        if (from == to) {
            std::cout << "Invalid recipient; cannot transfer to same account.\n";
            return;
        }

        double amount;
        std::cout << "Enter amount: ";
        std::cin >> amount;

        if (from->transfer(*to, amount)) {
            std::cout << "Transaction successful, new balance: $"
                      << std::fixed << std::setprecision(2) << from->balance << '\n';
        } else {
            std::cout << "Transaction failed; invalid amount.\n";
        }
    }

    void displayMenu() {
        std::cout << "===== BANKING SYSTEM =====\n";
        std::cout << "1. Register\n"
                  << "2. Create Account\n"
                  << "3. Deposit\n"
                  << "4. Withdraw\n"
                  << "5. Fund Transfer\n"
                  << "6. View Account Info & Balance\n"
                  << "7. View Transaction History\n"
                  << "8. View Customer Info\n"
                  << "9. Exit\n";
        std::cout << "Enter choice: ";
    }

    void run() {
        int choice;

        while (true) {
            displayMenu();
            std::cin >> choice;

            switch (choice) {
                case 1: createCustomer(); break;
                case 2: createAccount(); break;
                case 3: deposit(); break;
                case 4: withdraw(); break;
                case 5: transfer(); break;
                case 6:
                case 7: {
                    std::string number;
                    std::cout << "Enter account number: ";
                    std::cin >> number;

                    Account *acc = findAccount(number);
                    if (acc) {
                        if (choice == 6) {
                            acc->display();
                        } else {
                            acc->displayTransactions(10);
                        }
                    } else {
                        std::cout << "No account found with specified number.\n";
                    }

                    break;
                }
                case 8: {
                    std::string id;
                    std::cout << "Enter customer ID: ";
                    std::cin >> id;

                    Customer *c = findCustomer(id);
                    if (c) {
                        c->display();
                    } else {
                        std::cout << "No customer found with specified ID.\n";
                    }

                    break;
                }
                case 9: return;
                default:
                    std::cout << "Invalid choice.\n";
            }
        }
    }
};

int main() {
    BankingSystem bank;
    bank.run();
    return 0;
}