
#include "Book.h"


void Book::setTitle(string t){title = t;}

void Book::setAuthor(string a){author = a;}

void Book::setGenre(string g){category = g;}

string Book::getTitle() {return title;}

string Book::getAuthor() {return author;}

string Book::getCategory() {return category;}

bool Book::isBorrowedStatus() {return isBorrowed;}

void Book::markAsBorrowed() {isBorrowed = true;}

void Book::markAsReturned() {isBorrowed = false;}
