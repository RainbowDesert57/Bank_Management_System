#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Account
    {
        string holderName;
        int accountNo;
        double balance;
    };

void saveAccount (Account& acc);
void depositMoney(vector<Account>& accounts);
vector<Account> readAllAccounts();
void withdrawMoney(vector<Account>& accounts);
void closeAccount(vector<Account>& accounts);


void saveAccount (Account& acc)
{
    cout << "Enter account holder's name (use (_) instead of space): ";
    cin >> acc.holderName;
    cout << "Enter account number: ";
    cin >> acc.accountNo;
    cout << "Enter initial balance: ";
    cin >> acc.balance;

    ofstream outFile("accounts.txt", ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << acc.holderName << " " << acc.accountNo << " " << acc.balance << endl;
        outFile.close();
        cout << "Account saved successfully." << endl;
    }
    else
    {
        cout << "Error: Unable to open file." << endl;
    }
    system("pause");
}
vector<Account> readAllAccounts()
{
    vector<Account> accounts;
    ifstream inFile("accounts.txt");
    if (inFile.is_open()) 
    {
        cout << setw(30) << left << "Name" << setw(30) << "Account Number" << setw(20) << "Amount ($)" << endl;
        cout << setw(80) << setfill('-') << "" << endl;
        cout << setfill(' ');
        Account acc;
        while (inFile >> acc.holderName >> acc.accountNo >> acc.balance) 
        {
            cout << setw(30) << left << acc.holderName << setw(30) << acc.accountNo << setw(20) << acc.balance << endl;
            accounts.push_back(acc);
        }
        inFile.close();
    } 
    else 
    {
        cout << "Error: Unable to open file." << endl;
    }
    system("pause");
    return accounts;
}
void depositMoney(vector<Account>& accounts)
{
    int accountNo;
    double amount;
    cout << "\n" "Enter account number to deposit money: ";
    cin >> accountNo;
    cout << "Enter amount to deposit: $ ";
    cin >> amount;

    bool found = false;
    for (Account& acc : accounts)
    {
        if (acc.accountNo == accountNo)
        {
            acc.balance += amount;
            found = true;
            break;
        }
    }

    if (found)
    {
        cout << "Money deposited successfully." << endl;
        // Update the file with the new balance
        ofstream outFile("accounts.txt");
        if (outFile.is_open())
        {
            for (const Account& acc : accounts)
            {
                outFile << acc.holderName << " " << acc.accountNo << " " << acc.balance << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
    else
    {
        cout << "Account not found." << endl;
    }
    system("pause");
}
void withdrawMoney(vector<Account>& accounts)
{
    int accountNo;
    double amount;
    cout << "\n" "Enter account number to withdraw money from: ";
    cin >> accountNo;
    cout << "Enter amount to withdraw: $ ";
    cin >> amount;

    bool found = false;
    for (Account& acc : accounts)
    {
        if (acc.accountNo == accountNo)
        {
            if (acc.balance >= amount) // Check if there's enough balance to withdraw
            {
                acc.balance -= amount;
                found = true;
            }
            else
            {
                cout << "Insufficient balance." << endl;
            }
            break;
        }
    }

    if (found)
    {
        cout << "Money withdrawn successfully." << endl;
        // Update the file with the new balance
        ofstream outFile("accounts.txt");
        if (outFile.is_open())
        {
            for (const Account& acc : accounts)
            {
                outFile << acc.holderName << " " << acc.accountNo << " " << acc.balance << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
    else
    {
        cout << "Account not found." << endl;
    }
    system("pause");
}
void closeAccount(vector<Account>& accounts)
{
    int accountNo;
    cout << "\n" << "Enter account number to close the account: ";
    cin >> accountNo;

    bool found = false;
    for (auto it = accounts.begin(); it != accounts.end(); ++it)
    {
        if (it->accountNo == accountNo)
        {
            accounts.erase(it); // Remove the account from the vector
            found = true;
            break;
        }
    }

    if (found)
    {
        cout << "Account closed successfully." << endl;
        // Update the file with the updated account list
        ofstream outFile("accounts.txt");
        if (outFile.is_open())
        {
            for (const Account& acc : accounts)
            {
                outFile << acc.holderName << " " << acc.accountNo << " " << acc.balance << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
    else
    {
        cout << "Account not found." << endl;
    }
    system("pause");
}

    
int main()
{
    string choice;
    vector<Account> accounts;
    cout<<"\t\t -----------------------------------------"<<endl;
    cout<<"\t\t | Welcome to the Bank Management System |"<<endl;
    cout<<"\t\t -----------------------------------------"<<endl;

while(true)
{
    cout<<endl;
    cout<<"\t --- Main Menu ---"<<endl;
    cout<<"\t 1. Create Account"<<endl;     
    cout<<"\t 2. Deposit Money"<<endl; 
    cout<<"\t 3. Withdraw Money"<<endl;
    cout<<"\t 4. All Account Holder List"<<endl;
    cout<<"\t 5. Close an Account"<<endl;
    cout<<"\t 6. Exit"<<endl;
    cout<<endl;

    cout<<"\t Enter your choice (1-8): ";
    cin>>choice;

             if (choice == "1")
    {
        Account newAccount;
        saveAccount(newAccount);
    }
        else if (choice == "2")
    {
        accounts = readAllAccounts();
        depositMoney(accounts);
    }
        else if (choice == "3")
    {
        accounts = readAllAccounts();
        withdrawMoney(accounts);
    }
        else if (choice == "4")
    {
        accounts = readAllAccounts();
    }
        else if (choice == "5")
        {
            accounts = readAllAccounts();
            closeAccount(accounts);
        }
        else if (choice == "6")
    {
            break; // Exit the loop and end the program
    }
}
    return 0;
}
