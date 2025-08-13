#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"
#include "Library.h"
#include "librarian.h"
#include "customer.h"
#include "user.h"

using namespace std;


// Function to display the login menu
void logInMenu() {
    User* user = nullptr;  // Pointer to a User object (base class)
    string name, password;

    cout << "Enter username: ";
    cin >> name;

    // string to the path of the user's file based on their username
    string fileName = "users/" + name + "_folder/" + name + ".txt";
    ifstream inFile(fileName); // Opens file for reading

    // If file not found, user account does not exist
    if (!inFile) {
        cout << "No account with that username exists.\n";
        return;  // Exit the function early
    }

    // Variables to store data read from the user file
    string storedName, storedPassword;
    char accountType;

    // Read username, password and account type (L for Librarian, C for Customer) from file
    getline(inFile, storedName);
    getline(inFile, storedPassword);
    inFile >> accountType;

    cout << "Enter password: ";
    cin >> password;

    // Allow user up to 5 attempts to enter the correct password
    for (int i = 5; i > 0; i--) {
        if (password == storedPassword) {
            // Password matches, login successful
            cout << "Login successful! Account type: " << accountType << endl;

            // See either Librarian or Customer based on account type
            if (accountType == 'L') {
                user = new Librarian(accountType, name, password);
            } else if (accountType == 'C') {
                user = new Customer(accountType, name, password);
            }

            // Call the menu associated with the user type (Librarian or Customer)
            user->displayMenu();
            // Clean up dynamically allocated memory
            delete user;
            break; // Exit the loop after successful login
        } else {
            // Shows remaining tries if password is incorrect
            cout << "Incorrect password. You have (" << i << ") more tries: ";
            cin >> password;
        }
    }

    inFile.close(); // Close the user file
}

int main() {

 cout << "Welcome To Library Management System!" << endl;
    string option; // variable for menu choice

    while (true) {
        cout << endl << "Main Menu:" << endl;
        cout << "(1) Login" << endl;
        cout << "(0) Exit" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if (option == "1") {
            logInMenu();  // call the login menu function
        } else if (option == "0") {
            cout << "Exiting program..";
            break;  // exit the infinite loop and end the program
        } else {
            cout << "Invalid choice. Please enter 1 or 0: ";
        }
    }

    return 0; // program exit
}


