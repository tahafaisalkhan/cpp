# Telephone Directory

This project is a digital version of a telephone directory, implemented in C++. It is a project for the CS200 course. The program allows users to manage a directory of contacts, making it easier to search for phone numbers and other contact information. The project includes two main classes: `Entry` and `Directory`.

## Features

- Add, remove, and search for entries in the directory
- Search by name, phone number prefix, and city
- Display the entire directory
- Sort the directory in ascending order by name
- Save and load the directory from a file
- Combine two directories, ensuring no duplicate entries

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++, clang)

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/telephonedirectory.git
    cd telephonedirectory
    ```

2. Compile the program:

    ```bash
    g++ telephonedirectory.cpp -o telephonedirectory
    ```

3. Run the program:

    ```bash
    ./telephonedirectory
    ```

## Classes

### Entry Class

The `Entry` class contains the information for each entry in the directory.

- **Attributes:**
  - `name` (string): Name of the contact
  - `address` (string): Address of the contact
  - `phone_number` (string): Phone number of the contact

- **Methods:**
  - Default and parameterized constructors
  - Setter and getter functions for each attribute
  - `operator >>`: Input the details of this entry from the user, ensuring phone numbers are in the correct format
  - `operator <<`: Display the details of this entry
  - `operator ==`: Compare the phone numbers of two entries

### Directory Class

The `Directory` class manages multiple entries.

- **Attributes:**
  - `entries` (Entry*): Dynamically allocated array of `Entry` objects
  - `entries_made` (int): Total number of entries in the directory

- **Methods:**
  - Default and parameterized constructors, and destructor
  - `addEntry()`: Add a new entry to the directory, checking for duplicates
  - `removeEntry(string phone_num)`: Remove an entry by phone number
  - `lookup(string name)`: Find and display entries with the same name
  - `lookupPrefix(string prefix)`: Find and display phone numbers starting with a given prefix
  - `lookupCity(string city)`: Search and display addresses with the given city name
  - `operator <<`: Display the entire directory
  - `sortAscending()`: Sort the directory in ascending order by name
  - `operator +`: Combine two directories, ensuring no duplicate entries
  - `saveDirectory()`: Save the directory to a `.txt` file
  - `loadDirectory()`: Load the directory from a `.txt` file

## Main Function

The main function displays a menu to the user for interacting with the directory. The menu includes options to add, remove, search, display, sort, save, and load entries. The program continues to display the menu until the user chooses to quit.

## How to Use

1. When the program starts, choose between loading a saved directory or starting a new one.
2. Use the main menu to interact with the directory:
   - Add, remove, or search for entries
   - Display the entire directory
   - Sort the directory by name
   - Save or load the directory from a file
   - Combine directories to test the overloaded `+` function
3. The program handles errors and continues running until the user chooses to quit.

## Acknowledgements

- This project is part of the CS200 course assignments.
- Thanks to the course instructors for their guidance and support.
