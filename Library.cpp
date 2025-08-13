#include "library.h"


// Constructor that Loads all books from files in the "Books" folder into the books (catalog) array.
Library::Library() {
    bookCount = 0;

    // loop through each file in "Books" folder
    for (const auto& entry : fs::directory_iterator("Books")) {
        string filePath = entry.path().string();
        ifstream userFile(filePath);

        // If the file opens successfully, read book data line by line
        if (userFile.is_open()) {
            string title, author, genre, isborrowed;
            getline(userFile, title);
            getline(userFile, author);
            getline(userFile, genre);
            getline(userFile, isborrowed);
            userFile.close();

            // Set the book in the catalog array
            catalog[bookCount].setTitle(title);
            catalog[bookCount].setAuthor(author);
            catalog[bookCount].setGenre(genre);

            // Mark book as borrowed or returned based on file data.
            if (isborrowed == "borrowed") catalog[bookCount].markAsBorrowed();
            else if (isborrowed == "unborrowed") catalog[bookCount].markAsReturned();

            bookCount++;  // adds to total book count.
        } else {
            cout << "Could not open file: " << endl;
        }
    }
}

// Adds a new book to the catalog array.
void Library::addBook() {
    cin.ignore();
    string title, author, genre;

    // Check if array of books in library has space for more books.
    if (bookCount <= 100) {
        cout << "Enter Title Name:"; getline(cin, title);
        cout << "\nEnter Author Name: "; getline(cin, author);
        cout << "\nEnter The Genre: "; cin >> genre;
        cin.ignore();

        // Set book info and mark it as returned (available).
        catalog[bookCount].setTitle(title);
        catalog[bookCount].setAuthor(author);
        catalog[bookCount].setGenre(genre);
        catalog[bookCount].markAsReturned();

        bookCount++;  // Increase book count.
    } else {
        cout << "Maximum Books Added To Library!";
    }
}

// Removes a book from the catalog and deletes its file.
void Library::removeBook() {
    string title;
    bool isFound = false;
    int index_locator;

    cin.ignore();
    cout << "Enter Title name of Book you want to remove: ";
    getline(cin, title);

    // Search for the book by title
    for (int i = 0; i < bookCount; i++) {
        if (title == catalog[i].getTitle()) {
            index_locator = i;
            isFound = true;
        }
    }

           if (isFound) {
        // Shift books to overwrite the removed book from the array of books (catalog)
        for (int i = index_locator; i < bookCount - 1; i++) {
            catalog[i] = catalog[i + 1];
        }

        bookCount--;  // decreases book count

        // Remove the file from disk.
        string fileName = "Books/" + title + ".txt";
        fs::remove(fileName);


        cout << "Book Removed Successfully!";  // Inform user of success or failure
    } else if (!isFound) {
        cout << "Book Not Found";
    }
}

//  function that converts a string to uppercase for case-insensitive search.
string toUpper(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

// Finds a book by title (case-insensitive) and displays details if found
void Library::findByTitle() {
    cout << "Enter Title of Book: ";
    string title;
    cin.ignore();
    getline(cin, title);
    title = toUpper(title);

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        string BookTitleUpper = toUpper(catalog[i].getTitle());
        if (title == BookTitleUpper) {
            cout << "\nBook Found !" << endl;
            cout << catalog[i].getTitle() << " by: " << catalog[i].getAuthor()
                 << endl << "Genre: " << catalog[i].getCategory() << endl;
            if (catalog[i].isBorrowedStatus()) { cout << "(Borrowed)"; }
            else { cout << "(Not Borrowed)"; }
            cout << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Book Not Found!";
    }
}

// Finds books by author (case-insensitive) and prints them.
void Library::findByAuthor() {
    cout << "Enter Author of Book: ";
    string author;
    cin.ignore();
    getline(cin, author);
    author = toUpper(author);

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        string BookAuthorUpper = toUpper(catalog[i].getAuthor());
        if (author == BookAuthorUpper) {
            cout << "\nBook Found !" << endl;
            cout << catalog[i].getTitle() << " by: " << catalog[i].getAuthor()
                 << endl << "Genre: " << catalog[i].getCategory() << endl;
            if (catalog[i].isBorrowedStatus()) { cout << "(Borrowed)"; }
            else { cout << "(Not Borrowed)"; }
            cout << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Book Not Found!";
    }
}

// Finds books by category/genre (case-insensitive) and prints them.
void Library::findByCategory() {
    cout << "Enter Genre of Book: ";
    string genre;
    cin.ignore();
    cin >> genre;
    genre = toUpper(genre);

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        string BookGenreUpper = toUpper(catalog[i].getCategory());
        if (genre == BookGenreUpper) {
            cout << "\nBook Found !" << endl;
            cout << catalog[i].getTitle() << " by: " << catalog[i].getAuthor()
                 << endl << "Genre: " << catalog[i].getCategory() << endl;
            if (catalog[i].isBorrowedStatus()) { cout << "(Borrowed)"; }
            else { cout << "(Not Borrowed)"; }
            cout << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Book Not Found!";
    }
}

// Lists all currently borrowed books.
void Library::listBorrowed() {
    cout << endl << "[BORROWED BOOKS]:" << endl << endl;
    for (int i = 0; i < bookCount; i++) {
        if (catalog[i].isBorrowedStatus()) {
            cout << catalog[i].getTitle() << " by: " << catalog[i].getAuthor()
                 << ". Genre: " << catalog[i].getCategory() << endl;
        }
    }
}

// Lists all currently available (not borrowed) books.
void Library::isAvailable() {
    cout << endl << "[AVAILABLE BOOKS]:" << endl << endl;
    for (int i = 0; i < bookCount; i++) {
        if (!catalog[i].isBorrowedStatus()) {
            cout << catalog[i].getTitle() << " by: " << catalog[i].getAuthor()
                 << ". Genre: " << catalog[i].getCategory() << endl;
        }
    }
}

// Destructor that Saves all books in the array catalog back to their files in folder "Books" and creates new files for new books.
Library::~Library() {
    for (int i = 0; i < bookCount; i++) {
        string filename = "Books/" + catalog[i].getTitle() + ".txt";
        ofstream file(filename);

        file << catalog[i].getTitle() << '\n';
        file << catalog[i].getAuthor() << '\n';
        file << catalog[i].getCategory() << '\n';

        if (catalog[i].isBorrowedStatus()) {
            file << "borrowed" << '\n';
        } else {
            file << "unborrowed" << '\n';
        }

        file.close();
    }
}

