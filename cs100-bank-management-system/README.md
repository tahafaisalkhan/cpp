# CS100 Bank Management System

This project is a simple bank management system created as part of the CS100 course. It allows users to create new accounts, withdraw and deposit money, request loans, and print balance statements. The system uses file handling to store and retrieve user information.

## Features

- Create new accounts with a randomly generated credit card number and user-defined PIN.
- Withdraw money, ensuring that a minimum balance is maintained.
- Deposit money into accounts.
- Request loans based on account balance.
- Print a balance statement showing the current balance and outstanding loans.

## Required Libraries

```cpp
#include <iostream>      // For standard stream objects
#include <iomanip>       // For parametric manipulators
#include <string>        // For string functions
#include <cstdlib>       // For randomisation/system commands
#include <ctime>         // For randomisation functions
#include <fstream>       // For file handling
#include <unistd.h>      // For system colors
using namespace std;
