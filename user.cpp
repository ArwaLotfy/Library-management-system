#include <iostream>
#include <string>
#include "User.h"



using namespace std;

User::User(char t, string n, string p){id = t; name = n; password = p;}
string User::getUser(){return name;}
