#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string category;
    bool isBorrowed;

public:
    void setTitle(string t);
    void setAuthor(string a);
    void setGenre(string g);
    string getTitle();
    string getAuthor();
    string getCategory();
    bool isBorrowedStatus();
    void markAsBorrowed();
    void markAsReturned();
};

#endif
