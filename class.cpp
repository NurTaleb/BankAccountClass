#include <iostream>
#include <string>
#include <fstream>  // We use this to save and load data from a file

using namespace std;

// This is a "Bank Account" class that holds the details of one bank account
class BankAccount {
private:
    int accountNumber;    // Account number of the user (a unique ID)
    string ownerName;     // The name of the person who owns the account
    double balance;       // The amount of money in the account

public:
    // This is the constructor that creates a bank account with the account number, owner name, and balance
    BankAccount(int accNum, string name, double initialDeposit) {
        accountNumber = accNum;    // Set account number
        ownerName = name;          // Set owner's name
        balance = initialDeposit;  // Set initial balance
    }

    // Function to deposit money into the account
    void deposit(double amount) {
        if (amount > 0) {  // If the deposit amount is greater than zero
            balance += amount;  // Add the deposit amount to the balance
            cout << "Deposited: $" << amount << endl;  // Show how much money was deposited
        } else {
            cout << "Invalid deposit amount." << endl;  // If the deposit is less than or equal to zero, show an error
        }
    }

    // Function to withdraw money from the account
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {  // If the withdrawal amount is valid and you have enough balance
            balance -= amount;  // Subtract the withdrawal amount from the balance
            cout << "Withdrew: $" << amount << endl;  // Show how much money was withdrawn
        } else if (amount > balance) {
            cout << "Insufficient funds!" << endl;  // If you don’t have enough money, show this message
        } else {
            cout << "Invalid withdrawal amount." << endl;  // If the amount is negative, show an error
        }
    }

    // Function to check how much money is in the account
    void checkBalance() const {
        cout << "Current balance: $" << balance << endl;  // Display the current balance
    }

    // Function to show all the details of the account
    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Owner Name: " << ownerName << endl;
        cout << "Balance: $" << balance << endl;  // Show the account number, owner's name, and balance
    }

    // Function to save the account's data into a file
    void saveAccountToFile(ofstream& outFile) {
        outFile << accountNumber << "\n" << ownerName << "\n" << balance << "\n";  // Write the account data to the file
    }

    // Static function to load account data from a file
    static BankAccount loadAccountFromFile(ifstream& inFile) {
        int accNum;
        string name;
        double bal;

        inFile >> accNum;  // Read the account number from the file
        inFile.ignore();  // Ignore the newline character after the account number
        getline(inFile, name);  // Read the owner's name from the file
        inFile >> bal;  // Read the balance from the file

        return BankAccount(accNum, name, bal);  // Return a new account with the loaded data
    }
};

// This function shows the menu with options for the user to choose from
void displayMenu() {
    cout << "\nBank Account Management System\n";
    cout << "1. Create Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. Display Account Information\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    BankAccount* account = nullptr;  // We start with no account, set it to "nullptr"
    int choice;                      // This will store the user's choice from the menu
    int accountNumber = 1000;        // Start account number from 1000 (it will increase with each new account)
    string ownerName;                // The owner's name
    double initialDeposit;           // The initial money the user wants to deposit when creating the account
    
    while (true) {  // This will keep running the menu until the user chooses to exit
        displayMenu();  // Display the menu with options
        cin >> choice;  // Get the user's choice

        switch (choice) {  // Based on the user's choice, do different actions
            case 1:  // If the user chooses "Create Account"
                cout << "Enter your name: ";
                cin.ignore();  // Ignore the extra newline left after reading the number
                getline(cin, ownerName);  // Get the owner's name from user input
                cout << "Enter initial deposit: $";
                cin >> initialDeposit;  // Get the initial deposit amount

                // Create a new bank account with the entered details
                account = new BankAccount(accountNumber++, ownerName, initialDeposit);
                cout << "Account created successfully.\n";  // Let the user know the account was created
                break;

            case 2:  // If the user chooses "Deposit Money"
                if (account != nullptr) {  // If an account has been created
                    double depositAmount;
                    cout << "Enter deposit amount: $";
                    cin >> depositAmount;  // Get the deposit amount from user input
                    account->deposit(depositAmount);  // Call the deposit function
                } else {
                    cout << "No account created yet.\n";  // If no account was created, show this message
                }
                break;

            case 3:  // If the user chooses "Withdraw Money"
                if (account != nullptr) {  // If an account has been created
                    double withdrawAmount;
                    cout << "Enter withdrawal amount: $";
                    cin >> withdrawAmount;  // Get the withdrawal amount from user input
                    account->withdraw(withdrawAmount);  // Call the withdraw function
                } else {
                    cout << "No account created yet.\n";  // If no account was created, show this message
                }
                break;

            case 4:  // If the user chooses "Check Balance"
                if (account != nullptr) {  // If an account has been created
                    account->checkBalance();  // Show the current balance
                } else {
                    cout << "No account created yet.\n";  // If no account was created, show this message
                }
                break;

            case 5:  // If the user chooses "Display Account Information"
                if (account != nullptr) {  // If an account has been created
                    account->displayAccountInfo();  // Show the account information
                } else {
                    cout << "No account created yet.\n";  // If no account was created, show this message
                }
                break;

            case 6:  // If the user chooses "Exit"
                // Save account data to a file before exiting
                if (account != nullptr) {
                    ofstream outFile("account_data.txt");  // Open a file to save data
                    account->saveAccountToFile(outFile);  // Save the account data to the file
                    outFile.close();  // Close the file
                    cout << "Account data saved.\n";  // Let the user know the data was saved
                } else {
                    cout << "No account to save.\n";  // If there's no account to save, show this message
                }
                cout << "Exiting...\n";  // Exit the program
                delete account;  // Free the memory used by the account
                return 0;  // Exit the program

            default:
                cout << "Invalid choice. Please try again.\n";  // If the user enters a wrong choice
                break;
        }
    }
}
