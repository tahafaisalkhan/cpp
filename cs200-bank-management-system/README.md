# Basic Banking System

This project is a basic banking system implemented in C++ as a CS200 course assignment. The system uses inheritance and polymorphism to manage different types of accounts and user interactions. The project includes classes for `Person`, `Account`, `DebitAccount`, and `CreditAccount`.

## Features

- Create and manage debit and credit accounts
- Deposit and withdraw funds
- Transfer funds between accounts
- Display account details
- Handle error checking for account access

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++, clang)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/banking-system.git
    cd banking-system
    ```

2. Compile the program:

    ```bash
    g++ cs200bankaccount.cpp -o bankingsystem
    ```

3. Run the program:

    ```bash
    ./bankingsystem
    ```

## Classes

### Person Class

- **Attributes:**
  - `name` (string): Name of the person
  - `number` (string): Phone number
  - `email` (string): Email address
  - `address` (string): Address

- **Methods:**
  - Constructors
  - `displayDetails()`: Display the person's details

### Account Class

- **Attributes:**
  - `accountNumber` (int): Unique account number
  - `person` (Person): Associated person object

- **Methods:**
  - Constructors
  - `deposit(double amount)`: Deposit funds into the account
  - `withdraw(double amount)`: Withdraw funds from the account
  - `displayAccountDetails()`: Display account details
  - `transfer(Account* destAcc, double amount)`: Transfer funds to another account

### DebitAccount Class

- **Attributes:**
  - `balance` (double): Account balance

- **Methods:**
  - Constructors
  - `deposit(double amount)`: Deposit funds into the account
  - `withdraw(double amount)`: Withdraw funds from the account
  - `displayAccountDetails()`: Display account details
  - `transfer(Account* destAcc, double amount)`: Transfer funds to another account

### CreditAccount Class

- **Attributes:**
  - `balance` (double): Account balance
  - `creditLimit` (double): Credit limit

- **Methods:**
  - Constructors
  - `deposit(double amount)`: Deposit funds into the account
    - Deduct 20% interest if the balance is negative before deposit
  - `withdraw(double amount)`: Withdraw funds from the account
    - Balance can go negative up to the credit limit
  - `displayAccountDetails()`: Display account details
  - `transfer(Account* destAcc, double amount)`: Transfer funds to another account

## Interaction Overview

### Initial Menu

1. **Open Credit Account**
   - Ask for name, phone number, email, and address
   - Assign an account number

2. **Open Debit Account**
   - Ask for name, phone number, email, and address
   - Assign an account number

3. **Access Existing Account**
   - Prompt for account number
   - Present options:
     - Deposit
     - Withdraw
     - Transfer
     - Display Account Details
     - Exit to initial menu

### Error Handling

- Check for accessing accounts that do not exist

## Acknowledgements

- This project is part of the CS200 course assignments.
- Thanks to the course instructors for their guidance and support.
