#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include "Customer.h"
#include "Library.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using namespace std;


class Librarian : public User {
public:
    Library lib;
    Librarian(int id, string name, string passcode);

    void displayMenu() override;
    void addUser();
    void saveUserFile(string name, string password, char accountType);
    void removeUser();
    void listUsersData();
    void addBook();
    void deleteBook();
    void searchBook();
    void viewAllBooks();
    void viewBorrowedBooks();
    void viewUnborrowedBooks();
};

#endif
