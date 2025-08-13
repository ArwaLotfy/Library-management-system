#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Customer.h"
#include "Library.h"
#include <filesystem>
#include <fstream>
#include <string>
#include <iostream>

namespace fs = std::filesystem;
using namespace std;


class Customer : public User {
private:
    Book borrowedBooks[5];
    int borrowedCount;
    Library lib;

public:
    Customer(char t, string n, string p);
    void displayMenu() override;
    void borrowBook();
    void returnBook();
    void myBorrowedBooks();
    void searchBook();
    ~Customer();


};

#endif
