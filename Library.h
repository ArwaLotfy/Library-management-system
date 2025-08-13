#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>


namespace fs = std::filesystem;
using namespace std;

class Library {


public:
    Book catalog[100];
    Library();
    int bookCount;
    void addBook();
    void removeBook();
    void findByTitle();
    void findByAuthor();
    void findByCategory();
    void listBorrowed();
    void isAvailable();
    ~Library();
};

#endif
