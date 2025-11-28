#include "../include/Utils.h"

#include <iostream>

#include "../include/Colors.h"

using namespace std;

bool loggedIn = false;
bool superAdmin = false;

void invalid_input() {
    cin.clear();
    cin.ignore(1000, '\n');
}

void continueProcess() {
    cin.ignore();
    cout << RED << "\n\nPress Enter To Continue..." << RESET;
    cin.get();
    system("cls");
}