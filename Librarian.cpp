#include "Librarian.h"

// Constructor for Librarian class that initializes Librarian object by calling User class constructor.
Librarian::Librarian(int t, string n, string p) : User(t, n, p) {
    id = t;
    name = n;
    password = p;
}

// Displays the main menu for the librarian and uses the user input for menu selection.
void Librarian::displayMenu() {
    int chooser;

    do {
        cout << "\nLibrarian menu:" << endl;
        cout << "(1) Add New Customer Account\n"
             << "(2) Remove Customer Account\n"
             << "(3) View Customer Data\n"
             << "(4) Add New Book\n"
             << "(5) Remove Book\n"
             << "(6) View All Books\n"
             << "(7) Search for Book\n"
             << "(8) View Borrowed Books\n"
             << "(9) View Unborrowed Books\n"
             << "(0) Exit\n"
             << ": ";
        cin >> chooser;

        // Switch-case to perform actions based on user choice
        switch (chooser) {
            case 1: addUser(); break;
            case 2: removeUser(); break;
            case 3: listUsersData(); break;
            case 4: addBook(); break;
            case 5: deleteBook(); break;
            case 6: viewAllBooks(); break;
            case 7: searchBook(); break;
            case 8: viewBorrowedBooks(); break;
            case 9: viewUnborrowedBooks(); break;
            case 0: cout << "Exiting librarian menu.\n"; return;  // Exit the menu loop.
            default: cout << "Invalid option. Try again.\n"; break;  // Handle invalid input.
        }

    } while (chooser != 0);
}

// Creates a new customer or librarian account and collects necessary data to send to saveToFile function.
void Librarian::addUser() {
    cout << "Create new customer account\n";
    string name, password;
    char accoutType;

    cout << "Enter customer username: ";
    cin >> name;

    cout << "Enter password (between 6-20 characters): ";
    while (true) {
        cin >> password;
        // loop until  password length is good.
        if (6 <= password.length() && password.length() <= 20) break;
        cout << "Password too short or too long, re-enter: ";
    }

    cout << "Do you want it (L) for Librarian Account \nOr (C) for Customer Account: ";
    cin >> accoutType;
    accoutType = toupper(accoutType);

    // loops to check account type input if valid.
    while (accoutType != 'C' && accoutType != 'L') {
        cout << "Invalid Input, Please Re-enter: ";
        cin >> accoutType;
        accoutType = toupper(accoutType);
    }

    // sends to Save user data to the create file for it.
    saveUserFile(name, password, accoutType);
}

void Librarian::saveUserFile(string name, string password, char accountType) {
    // naming user folder and filename
    string fileName = "users/" + name + "_folder/" + name + ".txt";

    // Create user folder and a folder for user books.
    fs::create_directory("users/" + name + "_folder");
    fs::create_directory("users/" + name + "_folder/Books");

    // Open file and write user details: username, password, and account type.
    ofstream outFile(fileName);
    outFile << name << endl;
    outFile << password << endl;
    outFile << accountType << endl;
    outFile.close();

    cout << "Customer saved successfully.\n";
}

// Removes a user account by deleting the user file
void Librarian::removeUser() {
    string name;
    cout << "Enter customer username to delete: ";
    cin >> name;

    string filename = "users/" + name + "_folder/" + name + ".txt";
    ifstream file(filename);

    // Check if the user file exists
    if (file) {
        file.close();
        // Delete the user file from filesystem
        fs::remove(filename);
        cout << "Removed User Successfully!" << endl;
        return;
    } else if (!file) {
        cout << "No User Found!" << endl;
        return;
    }
}

// Lists the data of a user by reading from their saved file
void Librarian::listUsersData() {
    cout << "Enter Username To Access Data: ";
    string username;
    cin >> username;

    string filePath = "users/" + username + "_folder/" + username + ".txt";
    ifstream file(filePath);

    if (file) {
        string storedUserName, storedPassword, storedAccountType;

        // adds stored user data from file to string so I can print.
        file >> storedUserName;
        file >> storedPassword;
        file >> storedAccountType;
        file.close();

        // Display the strings of user data.
        cout << "Account name: " << storedUserName << endl;
        cout << "Account Password: " << storedPassword << endl;
        cout << "Account Type: " << storedAccountType << endl;
    } else {
        cout << "User data not found." << endl;
    }
}

// Adding a new book to the Library by calling the function from library class.
void Librarian::addBook() {
    lib.addBook();
}

// Removing a book from the Library by calling the function from library class.
void Librarian::deleteBook() {
    lib.removeBook();
}

// Displays all books in the Library.
void Librarian::viewAllBooks() {
    for (int i = 0; i < lib.bookCount; i++) {
        cout << lib.catalog[i].getTitle() << " by " << lib.catalog[i].getAuthor()
             << " [" << lib.catalog[i].getCategory() << "] ";

        // Display borrow status of each book
        if (lib.catalog[i].isBorrowedStatus()) {
            cout << "(Borrowed)";
        } else {
            cout << "(Not Borrowed)";
        }

        cout << endl;
    }
}

// Displaying borrowed books from the Library by calling the function from library class.
void Librarian::viewBorrowedBooks() {
    lib.listBorrowed();
}

// Displaying Available books from the Library by calling the function from library class.
void Librarian::viewUnborrowedBooks() {
    lib.isAvailable();
}

// Mini-menu for searching books by title, author, or genre and then calling the function from library class.
void Librarian::searchBook() {
    cout << "Search By (1) Title (2) Author (3) Genre: ";
    string chooser;
    cin.ignore();
    cin >> chooser;

    // loops till the input is valid
    while (chooser != "1" && chooser != "2" && chooser != "3") {
        cout << "Invalid Option, Please Re-enter: ";
        cin >> chooser;
    }

    // Call the functions based on the input
    if (chooser == "1") {
        lib.findByTitle();
    } else if (chooser == "2") {
        lib.findByAuthor();
    } else if (chooser == "3") {
        lib.findByCategory();
    }
}
