#include "Customer.h"


// Constructor that sets up the customer and loads borrowed books from files if any.
Customer::Customer(char t, string n, string p) : User(t, n, p), borrowedCount(0) {
    id = t;
    name = n;
    password = p;
    borrowedCount = 0; // start with 0 borrowed books

    string bookFolder = "users/" + name + "_folder/Books"; // path folder where user's borrowed books are saved

    // go through each file (book) in the folder
    for (const auto& entry : fs::directory_iterator(bookFolder)) {
        if (entry.is_regular_file()) {
            string filePath = entry.path().string(); // get the file path by reading it's name.
            ifstream userFile(filePath); // open the file

            if (userFile) {
                string title, author, genre, isborrowed;
                getline(userFile, title);
                getline(userFile, author);
                getline(userFile, genre);
                getline(userFile, isborrowed);
                userFile.close();

                // save book data into borrowedBooks array
                borrowedBooks[borrowedCount].setTitle(title);
                borrowedBooks[borrowedCount].setAuthor(author);
                borrowedBooks[borrowedCount].setGenre(genre);

                // set book status depending on the line written in the file
                if (isborrowed == "borrowed") borrowedBooks[borrowedCount].markAsBorrowed();
                else if (isborrowed == "unborrowed") borrowedBooks[borrowedCount].markAsReturned();

                borrowedCount++; // adds counter by one
            } else if (!userFile){
                cout << "Could not open file: " << endl;
            }
        }
    }
}

// Shows the customer menu and handles the choices.
void Customer::displayMenu() {
    int choice;
    do {
        cout << "\nCustomer Menu:\n";
        cout << "(1) Search for Book\n";
        cout << "(2) View My Borrowed Books\n";
        cout << "(3) Borrow a Book\n";
        cout << "(4) Return a Book\n";
        cout << "(0) Exit\n: ";
        cin >> choice;

        // Run the matching function
        switch (choice) {
            case 1: searchBook(); break;
            case 2: myBorrowedBooks(); break;
            case 3: borrowBook(); break;
            case 4: returnBook(); break;
            case 0: cout << "Exiting\n"; return;
            default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 0);
}

// Changes all letters in a string to capital letters
string toUpperz(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

// Allows the customer to borrow a book
void Customer::borrowBook() {
    lib.isAvailable(); // show all available books
    cout << endl;

    if (borrowedCount <= 5) { // make sure they didn’t hit the maximum borrowed count
        bool isFound = false;
        cout << "Enter The (Title) of The Book You Want To Borrow: ";
        string title;
        cin.ignore();
        getline(cin, title);
        title = toUpperz(title); // convert input to uppercase for (case-insensitive)

        // check if book exists in the catalog
        for (int i = 0; i < lib.bookCount; i++) {
            string bookTitle = lib.catalog[i].getTitle();
            bookTitle = toUpperz(bookTitle);

            if (title == bookTitle) {
                isFound = true;
                borrowedBooks[borrowedCount] = lib.catalog[i]; // add to user's list
                lib.catalog[i].markAsBorrowed(); // mark it as borrowed in library
                borrowedCount++; // increase count
                cout << "Borrowed successfully!" << endl;
            }
        }

        if (!isFound) {
            cout << "Book Not Found!";
        }
    } else {
        cout << "Maximum Books Borrowed!" << endl;
    }
}

// Returns any borrowed books from the customer
void Customer::returnBook() {
    if (borrowedCount > 0) { // make sure they have books before using the function
        myBorrowedBooks(); // calls function that shows borrowed books
        cout << endl;
        cout << "Enter The (Title) of The Book You Want To Return: ";
        string title;
        int index_locator = -1;
        cin.ignore();
        getline(cin, title);
        title = toUpperz(title);
        bool isFound = false;

        // Find the book in borrowedBooks
        for (int i = 0; i < borrowedCount; i++) {
            string bookTitle = borrowedBooks[i].getTitle();
            bookTitle = toUpperz(bookTitle);

            if (title == bookTitle) {
                index_locator = i;
                isFound = true;
                // delete the file of this book in the borrowed books folder of the user
                string filePath = "users/" + name + "_folder/Books/" + borrowedBooks[i].getTitle() + ".txt";
                fs::remove(filePath.c_str());
            }
        }

        if (isFound){

            // mark the book as returned in the library class
            for (int i = 0; i < lib.bookCount; i++) {
                if (title == lib.catalog[i].getTitle()) {
                    lib.catalog[i].markAsReturned();
                }
            }

            // remove the returned book from borrowedBooks by shifting the array to the left
            for (int i = index_locator; i < borrowedCount - 1; i++) {
                borrowedBooks[i] = borrowedBooks[i + 1];
            }

            borrowedCount--; // reduce the borrowed counter for any further loops.
            cout << "Returned successfully!" << endl;
        }
         else if (!isFound){cout << "Book Not Found!";}
    }

     else {
        cout << "No Borrowed Books!" << endl;
    }
}

// Shows all books that the customer borrowed
void Customer::myBorrowedBooks() {
    cout << endl << "[BOOKS BORROWED]:" << endl;

    for (int i = 0; i < borrowedCount; i++) {
        cout << borrowedBooks[i].getTitle() << " by " << borrowedBooks[i].getAuthor()
             << " [" << borrowedBooks[i].getCategory() << "]" << endl;
    }
}

// Mini-menu for searching books by title, author, or genre and then calling the function from library class.
void Customer::searchBook() {
    cout << "Search By (1) Title (2) Author (3) Genre: ";
    string chooser;
    cin.ignore();
    cin >> chooser;

    while (chooser != "1" && chooser != "2" && chooser != "3") {
        cout << "Invalid Option, Please Re-enter: ";
        cin >> chooser;
    }

    // Calls the functions based on the input.
    if (chooser == "1") {
        lib.findByTitle();
    } else if (chooser == "2") {
        lib.findByAuthor();
    } else if (chooser == "3") {
        lib.findByCategory();
    }
}

// Destructor that saves all borrowed books back to files and adds the new ones.
Customer::~Customer() {
    for (int i = 0; i < borrowedCount; i++) {
        ofstream fileName("users/" + name + "_folder/Books/" + borrowedBooks[i].getTitle() + ".txt");
        fileName << borrowedBooks[i].getTitle() << '\n';
        fileName << borrowedBooks[i].getAuthor() << '\n';
        fileName << borrowedBooks[i].getCategory() << '\n';
        fileName << "borrowed" << '\n';
        fileName.close();
    }
}





