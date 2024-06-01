// Required Libraries 
#include <iostream>                         // For standard stream objects
#include <iomanip>                          // For parametric manipulators
#include <string>                           // For string functions
#include <cstdlib>                          // For randomisation/system commands
#include <ctime>                            // For randomisation function                                          
#include <fstream>                          // For file handling
#include <unistd.h>                         // For system colors
using namespace std; 

// File Handling System
void updatefile(int balance, int loan, string datanumber)
{
    fstream datafile, datafile2; 

    datafile.open("datafile.txt", ios::in);
    datafile2.open("datatemp.txt", ios::out);
    datafile2.close();
    datafile2.open("datatemp.txt", ios::app);

    string number, pass, waste1, waste2; 

    datafile>>number;

    while(!datafile.eof())
    {
        datafile2<<number<<endl;
        datafile>>pass;
        datafile2<<pass<<endl;
        if (number == datanumber)
        {
            datafile>>waste1; 
            datafile2<<balance<<endl;
            datafile>>waste2;
            datafile2<<loan<<endl; 
        }
        else
        {
            datafile>>waste1;
            datafile2<<waste1<<endl;  
            datafile>>waste2;
            datafile2<<waste2<<endl;
        }
        datafile>>number; 
    }
    datafile.close();
    datafile2.close();

    datafile.open("datafile.txt", ios::out);
    datafile2.open("datatemp.txt", ios::in); 

    string temp; 
    datafile2>>temp;

    while(!datafile2.eof())
    {
       datafile<<temp<<endl; 
       datafile2>>temp;
    } 

    datafile.close(); 
    datafile2.close();
}

// Menu interface function
void interface()
{
    cout << endl;
    cout << "\33[1;31;36m"<< "-----------------------------------------" << endl;
    cout << "\33[1;31;36m"<< "Welcome to Taha Faisal Khan's ATM Machine" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "-----------------------------------------" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "                  MENU                   " <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "-----------------------------------------" <<"\33[0m"<< endl;
        time_t now;
    time(&now);
    cout << "        " << ctime(&now);
    cout << "\33[1;31;36m"<< "-----------------------------------------" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "Input (c) to create new account" <<"\33[0m"<< endl; 
    cout << "\33[1;31;36m"<< "Input (w) to withdraw" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "Input (d) to deposit" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "Input (l) to request loan" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "Input (p) to print balance statement" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "Input (e) to exit ATM" <<"\33[0m"<< endl;
    cout << "\33[1;31;36m"<< "-----------------------------------------" <<"\33[0m"<< endl;
}

// Adding user information
void adduser()
{
    system("Color 06");
    fstream datafile; 

    int balance;
    string realpin, realnumber;
    
    system("cls");

    datafile.open("datafile.txt", ios::app); 

    cout << "===============================" << endl;
    cout << "     ADDING NEW USER PANEL" << endl;
    cout << "===============================" << endl;
        
    // Generating random 11 digit credit card number
            
        int a;
        srand(time(0));
            
        for(int count = 1; count <= 11; count++)
        {
            a=rand()%10;
            realnumber = realnumber + to_string(a);
        }

        datafile<<realnumber<<endl; 

    // Generating 4 digit pin
        int pin1=0;
        bool flag = false;

        while (!flag)
        {
            cout << "Enter a four digit code: " << endl;
            cin >> pin1;
            realpin = to_string(pin1);
            if(realpin.length()==4)
            {
                flag = true;
            }

            else
            {
                system("cls");
                cin.clear();
                cin.ignore(10000,'\n');
                cout << endl;
                cout << "\33[1;31;1m" << "Error: Please enter only 4 digits!" << "\33[0m" << endl;
            }
        }
        datafile<<realpin<<endl; 

    // Inputting initial balance
        bool flag2 = true;
        while(flag2)
        {
            cout << "Enter your balance: " << endl;
            cin >> balance;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout<< "\33[1;31;1m"<< "Incorrect balance!"<<"\33[0m" <<endl;
                flag = true;
            }
            if(balance<1000)
            {
                system("CLS");
                cout << endl;
                cout << "\33[1;31;1m"<< "You need atleast $1000 to start your account!/Incorrect Input!" <<"\33[0m" << endl;
            }
            else if (balance>100000000)
            {
                system("CLS");
                cout << endl;
                cout << "\33[1;31;1m"<< "ATM limit exceeded!" <<"\33[0m"<< endl;
            }
            else
            {
                flag2 = false;
            }
        }
        flag = false;
        datafile<<balance<<endl; 
        datafile<<"0"<<endl; 
        cin.clear(); 
        cin.ignore(1000, '\n');
        
    system("CLS");
    // Output of username
        cout << endl;
        cout << "Your credit card number is: " << realnumber << endl;
        cout << "Your credit card pin is: " << realpin << endl;
        cout << "Your current balance is: $" << balance << endl;
        cout << endl;
    datafile.close();  

}

//Account validation
bool validation(int& balance, int& loan, string& datanumber, string& datapass, string& databalance, string& dataloan)
{
    system("cls");

    string cnumber;
    string pin;
    bool flag3 = false, num = false;
    fstream datafile; 
    bool flagx = true;

    datafile.open("datafile.txt", ios::in); 

    cout << endl;
    cout << "================================" << endl;
    cout << "         VALIDATION PANEL" << endl;
    cout << "================================" << endl;            
    
    cout << "Enter your 11 digit card number: " << endl;
    cin >> cnumber;
    cout << "Enter your 4 digit pin: " << endl;
    cin >> pin;

    system("CLS");

    while(!datafile.eof())
    {
        datafile>>datanumber;
        datafile>>datapass; 
        datafile>>databalance; 
        datafile>>dataloan;  
      
        if(datanumber == cnumber)
        {
            if(datapass == pin)
            { 
                num = true; 
                flag3 = true; 
                break; 
            }
            else
            {
                num = true; 
                break; 
            }
        }
    }

    balance = stoi(databalance); 
    loan = stoi(dataloan); 

    datafile.close(); 

    if(num == false)
    {
       cout<< "\33[1;31;1m"<<"Card Number not found"<<"\33[0m"<<endl; 
       return true; 
    }
    else if(flag3 == false)
    {
       cout<< "\33[1;31;1m"<<"Incorrect Pin"<<"\33[0m"<<endl; 
       return true; 
    }
    else
    {
        return false; 
    }

}

// Withdrawing money
int withdraw(int& balance, int& loan, string datanumber)
{   
    system("Color 0D");
    bool flag = true;
    int quantity;
    system("CLS");

    while(flag == true)
    {
        cout <<"What amount would you like to withdraw: " << endl;
        cin >> quantity;
        system("CLS");
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout<< "\33[1;31;1m"<<"Incorrect Input"<<"\33[0m"<<endl;
            flag = true;
        }
        if((balance-quantity) <1000)
        {
            cout<< "\33[1;31;1m" << "Withdraw amount more than minimum balance" <<"\33[0m"<< endl;
        }
        else
        {
            balance = balance - quantity;
            break;
        }
    }
    cout << "Withdrawn: " << quantity << endl;
    cout << "Total Balance: " << balance << endl;
    updatefile(balance, loan, datanumber); 

    return balance;
    
}

// Depositing Money
int deposit(int& balance, int& loan, string datanumber)
{
    system("Color 0D");
    system("CLS");
    bool flag = true;
    int deposit = 0;
    while(flag==true)
    {
        cout << "Enter amount to be deposited:" << endl;
        cin >> deposit;
        if(cin.fail())
        {
            system("CLS");
            cin.clear();
            cin.ignore();
            cout<< "\33[1;31;1m"<<"Incorrect Input"<<"\33[0m"<<endl;
            flag = true;
        }
        else
        {
            balance = balance + deposit;
            flag = false;
            break;
        }
    }
    
    system("CLS");
    cout <<"Deposited: " << deposit << endl;
    cout << "Current account balance: " << balance << endl;
    flag = false;

    updatefile(balance, loan, datanumber); 

    return balance;
}

// Request loan
int loanreq(int& balance, int& loan, string datanumber)
{
    system("CLS");
    system("Color 0D");
    if (balance<1000)
    {
        cout << "\33[1;31;1m"<< "Cannot take loan due to low account balance" <<"\33[0m"<< endl;
    }
    else
    {
        bool flag = true;
        int loan1=0;

        while(flag == true)
        {
            cout << "Enter required loan: " << endl;
            cin >> loan1;
            if(cin.fail())
            {
                system("CLS");
                cin.clear();
                cin.ignore();
                cout<< "\33[1;31;1m"<<"Incorrect Input"<<"\33[0m"<<endl;
                flag = true;
            }
            else
            {
                flag=false;
                break;
            }
        }
        system("CLS");
        cout << "Loan taken: " << loan1 << endl;
        loan = loan + loan1;
        cout << "Total Unpaid Loan: " << loan << endl; 
    }

    updatefile(balance, loan, datanumber); 

    return balance;
}

// Print balance statement
void statement(int balance, string realpin, string realnumber, int loan)
{
    system("Color 03");
    system("CLS");
    cout << endl;
    cout << "================================" << endl;
    cout << "            STATEMENT" << endl;
    cout << "================================" << endl;
    time_t now;
    time(&now);
    cout << "    " << ctime(&now);
    cout << "================================" << endl;   
    cout << " Credit Card Number: " << realnumber << endl;
    cout << " Current Balance: $" << balance << endl; 
    cout << " Loan Taken: $" << loan << endl; 
    cout << "================================" << endl;   
}

// Main function
int main()
{
    //Variables Updated Through Reference
    int balance, loan; 
    string datanumber, datapass, databalance, dataloan; 
    bool flagmain = true, flagy = true; 
    string com; 

    // Main command panel
    while(flagmain)
    {

        char command; 
        interface();
        cin >> command;

        switch(command)
        {
            case 'c':
            {
                adduser();
                sleep(5);
            } 
            break;

            case 'w':
            {
                if(validation(balance, loan, datanumber, datapass, databalance, dataloan))
                {
                    sleep(5);
                    break;
                }
                withdraw(balance, loan, datanumber);
                sleep(5);
            }
            break;

            case 'd':
            {
                if(validation(balance, loan, datanumber, datapass, databalance, dataloan))
                {
                    sleep(5);
                    break;
                }
                deposit(balance, loan, datanumber);
                sleep(5);
            }
            break;

            case 'l':
            {
                if(validation(balance, loan, datanumber, datapass, databalance, dataloan))
                {
                    sleep(5);
                    break;
                }
                loanreq(balance, loan, datanumber);
                sleep(5);
            }
            break;

            case 'p':
            {
                if(validation(balance, loan, datanumber, datapass, databalance, dataloan))
                {
                    sleep(5);
                    break;
                }
                statement(balance, datapass, datanumber, loan);
                sleep(5);
            }
            break;

            case 'e':
            {
                cout << "\33[1;31;1m"<< "Exiting ATM..." <<"\33[0m"<< endl;
                return 0;
            }

            default:
            {
                system("cls"); 
            }
            break;
        }
    }

    return 0;

}