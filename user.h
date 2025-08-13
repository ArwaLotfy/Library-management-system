#include <iostream>
#include <string>
#ifndef USER_H
#define USER_H


using namespace std;

class User{

protected:
char id;
string name;
string password;

public:
    User(string n = "", string p = "") : name(n), password(p) {}
    virtual ~User() {}
    User(char t, string n, string p);
    string getUser();
    virtual void displayMenu() = 0;

};
#endif


