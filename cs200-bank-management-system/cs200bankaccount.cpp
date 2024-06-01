//Note: Account number is a 4 digit randomized number
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <string>
using namespace std;

class Person
{
protected:
    string name;
    string number;
    string email;
    string address;

public:
    Person();
    Person(string n, string num, string em, string addy);
    void displayDetails();
};
Person::Person()
{
    name = "";
    number = "";
    email = "";
    address = "";
}
Person::Person(string n, string num, string em, string addy)
{
    name = n;
    number = num;
    email = em;
    address = addy;
}
void Person::displayDetails()
{
    cout << "Name: " << name << "\nNumber: " << number << "\nEmail: " << email << "\nAddress: " << address << endl;
}
class Account
{
protected:
    int account_number;
    Person *person;

public:
    Account();
    Account(int an, Person *p);
    int getAccountNumber();
    virtual ~Account();
    virtual bool deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void displayAccountDetails() = 0;
    virtual void transfer(Account *destAcc, double amount) = 0;
};
int Account::getAccountNumber()
{
    return account_number;
}
Account::Account()
{
    account_number = 0;
    person = nullptr;
}
Account::Account(int an, Person *p)
{
    account_number = an;
    person = p;
}
Account::~Account()
{
    delete person;
}
class DebitAccount : public Account
{
protected:
    double balance;

public:
    DebitAccount();
    DebitAccount(double b, int an1, Person *p1);
    bool deposit(double amount);
    void withdraw(double amount);
    void displayAccountDetails();
    void transfer(Account *destAcc, double amount);
};
DebitAccount::DebitAccount()
{
    balance = 0;
}
DebitAccount::DebitAccount(double b, int an1, Person *p1) : Account(an1, p1)
{
    balance = b;
}
bool DebitAccount::deposit(double amount)
{
    balance += amount;
    return true;
}
void DebitAccount::withdraw(double amount)
{
    if (balance >= amount)
    {
        balance -= amount;
    }
    else
    {
        cout << "Insufficient funds." << endl;
    }
}
void DebitAccount::displayAccountDetails()
{
    cout << "Account Number: " << account_number << endl;
    person->displayDetails();
    cout << "Balance: " << balance << endl;
}
void DebitAccount::transfer(Account *destAcc, double amount)
{
    if (balance >= amount)
    {
        withdraw(amount);
        destAcc->deposit(amount);
    }
    else
    {
        cout << "Insufficient funds for the transfer." << endl;
    }
}
class CreditAccount : public Account
{
protected:
    double balance;
    double credit_limit;

public:
    CreditAccount();
    CreditAccount(double b, double cl, int an1, Person *p1);
    bool deposit(double amount);
    void withdraw(double amount);
    void displayAccountDetails();
    void transfer(Account *destAcc, double amount);
};
CreditAccount::CreditAccount()
{
    balance = 0;
    credit_limit = 30000;
}
CreditAccount::CreditAccount(double b, double cl, int an1, Person *p1) : Account(an1, p1)
{
    balance = b;
    credit_limit = 30000;
}
bool CreditAccount::deposit(double amount)
{
    if (balance < 0)
    {
        double interest = 0.2 * (-balance);
        amount -= interest;
    }
    if(balance+amount < -30000)
    {
        cout<<"Amount can not be deposited"<<endl; 
        return false;
    }
    balance += amount;
    if(balance<0)
    {
        credit_limit = 30000+balance;
    }
    return true;
}
void CreditAccount::withdraw(double amount)
{
    if (balance - amount >= -30000)
    {
        balance -= amount;
        if(balance<0)
        {
            credit_limit = 30000-balance;
        }
    }
    else
    {
        cout << "Withdrawal exceeds credit limit." << endl;
    }
}
void CreditAccount::displayAccountDetails()
{
    cout << "Account Number: " << account_number << endl;
    person->displayDetails();
    cout << "Balance: " << balance << "\nCredit Limit: " << credit_limit << endl;
}
void CreditAccount::transfer(Account *destAcc, double amount)
{
    if (balance - amount >= -30000)
    {
        if(destAcc->deposit(amount))
        {
            withdraw(amount);
        }
    }
    else
    {
        cout << "Insufficient funds for the transfer." << endl;
    }
}

int main()
{
    cout << "--------------------------------" << endl;
    cout << "Welcome to Taha's Banking System" << endl;
    cout << "--------------------------------" << endl;

    char choice;
    int capacity = 10;
    Account **accounts = new Account *[capacity];
    int numAccounts = 0;

    do
    {
        cout << "\nInitial Menu:\n";
        cout << "1. Open Credit Account\n";
        cout << "2. Open Debit Account\n";
        cout << "3. Access Existing Account\n";
        cout << "4. Exit\n";

        bool flag = true;
        while (flag)
        {
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == '1' || choice == '2' || choice == '3' || choice == '4')
            {
                flag = false;
                break;
            }
            else
            {
                cout << "Invalid choice. Please enter a valid integer.\n";
            }
        }

        switch (choice)
        {
        case '1':
        {
            string name, email, address, number;
            int initial;
            bool flag = true;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your email: ";
            cin >> email;
            cout << "What is your number: ";
            cin>> number;
            cout << "Enter your address: ";
            cin >> address;
            
            while(flag==true)
            {
                cout << "Enter your initial balance: ";
                cin >> initial;
                if (initial<5000 || initial < 0)
                {
                    flag = true;
                }
                else
                {
                    cout << "Incorrect Input! Try Again!" << endl;
                    flag = false;
                }
            }

            srand(time(0));
            int accountNumber = (rand() % 9000) + 1000;
            cout << "Your account number is: " << accountNumber << endl;

            if (numAccounts == capacity)
            {
                capacity *= 2;
                Account **temp = new Account *[capacity];
                copy(accounts, accounts + numAccounts, temp); 
                delete[] accounts;
                accounts = temp;
            }

            accounts[numAccounts++] = new CreditAccount(initial, 30000, accountNumber, new Person(name, number, email, address));
            break;
        }

        case '2':
        {
            string name, email, address,number;
            bool flag2 = true;
            int initial;
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your email: ";
            cin >> email;
            cout << "What is your number: ";
            cin>> number;
            cout << "Enter your address: ";
            cin >> address;
            while(flag2==true)
            {
                cout << "Enter your initial balance: ";
                cin >> initial;
                if (initial<0)
                {
                    flag2 = true;
                }
                else
                {
                    cout << "Incorrect Input! Try Again!" << endl;
                    flag2 = false;
                }
            }
            int accountNumber = (rand() % 9000) + 1000;
            cout << "Your account number is: " << accountNumber << endl;

            if (numAccounts == capacity)
            {
                capacity *= 2;
                Account **temp = new Account *[capacity];
                copy(accounts, accounts + numAccounts, temp);
                delete[] accounts;
                accounts = temp;
            }

            accounts[numAccounts++] = new DebitAccount(initial, accountNumber, new Person(name, number, email, address));
            break;
        }

        case '3':
        {
            int accountNumber;
            cout << "Enter your account number: ";
            cin >> accountNumber;

            bool account_found = false;
            for (int i = 0; i < numAccounts; ++i)
            {
                if (accounts[i]->getAccountNumber() == accountNumber)
                {
                    account_found = true;

                    int account_choice;
                    do
                    {
                        cout << "\nAccount Menu:\n";
                        cout << "1. Deposit\n";
                        cout << "2. Withdraw\n";
                        cout << "3. Transfer\n";
                        cout << "4. Display Account Details\n";
                        cout << "5. Exit to Initial Menu\n";

                        while (true)
                        {
                            cout << "Enter your choice: ";
                            if (cin >> account_choice && account_choice >= 1 && account_choice <= 5)
                            {
                                break;
                            }
                            else
                            {
                                cin.clear();
                                cout << "Invalid choice. Please enter a valid integer.\n";
                            }
                        }

                        switch (account_choice)
                        {
                        case 1:
                        {
                            double amount;
                            cout << "Enter the deposit amount: ";
                            cin >> amount;
                            accounts[i]->deposit(amount);
                            break;
                        }
                        case 2:
                        {
                            double amount;
                            cout << "Enter the withdrawal amount: ";
                            cin >> amount;
                            accounts[i]->withdraw(amount);
                            break;
                        }
                        case 3:
                        {
                            int destAccountNumber;
                            cout << "Enter the destination account number: ";
                            cin >> destAccountNumber;

                            bool dest_account_found = false;
                            for (int j = 0; j < numAccounts; ++j)
                            {
                                if (accounts[j]->getAccountNumber() == destAccountNumber)
                                {
                                    dest_account_found = true;

                                    double transferAmount;
                                    cout << "Enter the amount to transfer: ";
                                    cin >> transferAmount;

                                    accounts[i]->transfer(accounts[j], transferAmount);
                                }
                            }
                            if (!dest_account_found)
                            {
                                cout << "Destination account not found.\n";
                            }
                            break;
                        }
                        case 4:
                            accounts[i]->displayAccountDetails();
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                            break;
                        }
                    } while (account_choice != 5);
                }
            }

            if (!account_found)
            {
                cout << "Account not found.\n";
            }

            break;
        }

        case '4':
            cout << "Exiting the program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (choice != '4');

    for (int i = 0; i < numAccounts; ++i)
    {
        delete accounts[i];
    }
    delete[] accounts;

    return 0;
}