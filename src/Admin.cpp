#include "../include/Admin.h"

#include <conio.h>

#include <iostream>

#include "../include/Colors.h"
#include "../include/Utils.h"

using namespace std;

Admin::Admin(bool super) : superAdmin(super) {
    setUsernameWithPrompt();
    setPasswordWithConfirmation();
}

Admin::Admin(const string& user, const string& pass, bool super) : superAdmin(super) {
    setUsername(user);
    setPassword(pass);
}

void Admin::setUsername(const string& user) {
    if (user.find(' ') != string::npos) {
        throw invalid_argument("Username cannot contain spaces.");
    }
    username = user;
}

string Admin::getUsername() const { return username; }

void Admin::setPassword(const string& pass) {
    if (pass.length() < 5) {
        throw invalid_argument("Password must be at least 5 characters long.");
    }
    password = pass;
}

string Admin::getPassword() const { return password; }

void Admin::setSuperAdmin(bool super) { superAdmin = super; }

bool Admin::isSuper() const { return superAdmin; }

void Admin::setUsernameWithPrompt() {
    string user;
    while (true) {
        cout << "Username: ";
        cin >> user;
        if (user.find(' ') != string::npos) {
            cout << "Username cannot contain spaces. Please try again.\n";
        } else {
            setUsername(user);
            break;
        }
    }
}

void Admin::setPasswordWithConfirmation() {
    password = getPasswordInput("Enter your password: ");
    while (password.length() < 5) {
        cout << RED << "Password must be at least 5 characters long. Please try again.\n" << RESET;
        password = getPasswordInput("Enter your password: ");
    }

    string confirmPassword = getPasswordInput("Confirm Password: ");
    while (password != confirmPassword) {
        cout << RED << "\nPasswords do not match, please try again.\n" << RESET;
        password = getPasswordInput("Enter your password: ");
        while (password.length() < 5) {
            cout << RED << "Password must be at least 5 characters long. Please try again.\n"
                 << RESET;
            password = getPasswordInput("Enter your password: ");
        }
        confirmPassword = getPasswordInput("Confirm Password: ");
    }
    cout << GREEN << "Password confirmed.\n" << RESET;
}

string Admin::getPasswordInput(const string& prompt) {
    string pass;
    char ch;
    cout << prompt;
    while (true) {
        ch = _getch();
        if (ch == 13) {
            cout << endl;
            break;
        } else if (ch == 8 && !pass.empty()) {
            cout << "\b \b";
            pass.pop_back();
        } else if (ch != 8 && ch != 13) {
            cout << '*';
            pass.push_back(ch);
        }
    }
    return pass;
}

bool checkAdmin(vector<Admin>& admins, string username, string password) {
    for (size_t i = 0; i < admins.size(); i++) {
        if (admins[i].getUsername() == username && admins[i].getPassword() == password) {
            if (admins[i].isSuper()) {
                ::superAdmin = true;
            } else {
                ::superAdmin = false;
            }
            return true;
        }
    }
    return false;
}

bool loginScreen(vector<Admin>& admins) {
    string username, password;
    char ch;
    cout << "\n\nLogin To Panel\n=================\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";

    ch = _getch();
    while (ch != 13) {
        if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }
    cout << endl;

    if (checkAdmin(admins, username, password)) {
        cin.get();
        system("cls");
        return true;
    } else {
        return false;
    }
}

void menuScreen(vector<Admin>& admins, vector<Customer>& customers, Hotel& hotel) {
    int option;
    string id;
    int custType;
    int cust;
    Customer* tempCust;

    cout << "Admin Panel\n=================\n";
    cout << "Select An Option (1-6)\n\n";
    cout << MAGENTA << "[1] " << RESET << "All Rooms" << endl;
    cout << MAGENTA << "[2] " << RESET << "All Customers" << endl;
    cout << MAGENTA << "[3] " << RESET << "Room Details" << endl;
    cout << MAGENTA << "[4] " << RESET << "Edit Room Price" << endl;
    cout << MAGENTA << "[5] " << RESET << "Book A Room" << endl;
    cout << MAGENTA << "[6] " << RESET << "Vacate A Room" << endl;
    if (::superAdmin) {
        cout << MAGENTA << "[7] " << RESET << "Add New Admin" << endl;
        cout << MAGENTA << "[8] " << RESET << "Logout" << endl;
    } else {
        cout << MAGENTA << "[7] " << RESET << "Logout" << endl;
    }
    cout << "\n> ";
    cin >> option;
    invalid_input();
    system("cls");

    switch (option) {
        case 1:
            cout << "All Rooms\n=================\nList of all rooms in the hotel\n\n";
            hotel.viewAllRooms();
            continueProcess();
            break;
        case 2:
            cout << "All Customers\n=================\nList of all registered customers in the "
                    "hotel\n\n";
            viewAllCustomers(customers);
            continueProcess();
            break;
        case 3:
            cout << "Room Details\n=================\nEnter a Room Number below to get the room "
                    "details\n\n";
            cout << "Room Number: ";
            cin >> id;
            cout << endl << endl;
            cust = hotel.checkRoom(id);
            checkCustomer(customers, cust);
            continueProcess();
            break;
        case 4:
            cout << "Edit Room Price\n=================\nEnter a Room Number below to edit it's "
                    "details\n\n";
            cout << "Room No: ";
            cin >> id;
            hotel.editRoom(id);
            continueProcess();
            break;
        case 5:
            cout << "Book A Room\n=================\nEnter a Room Number below to book a room\n\n";
            cout << "Room No: ";
            cin >> id;
            if (!hotel.isRoomAvailable(id)) {
                cout << RED << "Room " << id << " Is Not Available!" << RESET << endl;
                continueProcess();
                break;
            }
            cout << "Room Price ($): " << hotel.getRoomPrice(id) << endl;
            cout << "\nCustomer Type:\n"
                 << MAGENTA << "[1]" << RESET << " Existing\n"
                 << MAGENTA << "[2]" << RESET << " New Customer\n\n> ";
            cin >> custType;
            if (custType == 1) {
                cout << "Customer ID:";
                cin >> cust;
                tempCust = checkCustomer(customers, cust);
                if (tempCust != nullptr) {
                    hotel.bookRoom(id, *tempCust);
                } else {
                    cout << RED << "\nInvalid Customer ID!" << RESET;
                }
            } else if (custType == 2) {
                customers.push_back(Customer());
                hotel.bookRoom(id, customers.back());
            } else {
                cout << RED << "\nInvalid Choice!" << RESET;
            }
            continueProcess();
            break;
        case 6:
            cout << "Vacant A Room\n=================\nEnter a Room Number below to make a room "
                    "available\n\n";
            cout << "Room No:";
            cin >> id;
            hotel.vacateRoom(id);
            continueProcess();
            break;
        case 7:
            if (::superAdmin) {
                cout << "Add An Admin\n=================\nEnter a login credentials of the new "
                        "admin\n\n";
                admins.push_back(Admin());
                continueProcess();
            } else {
                ::loggedIn = false;
                system("cls");
                cout << GREEN << "Logged Out Successfully!...\n\n" << RESET;
            }
            break;
        case 8:
            if (::superAdmin) {
                ::loggedIn = false;
                system("cls");
                cout << GREEN << "Logged Out Successfully!...\n\n" << RESET;
            } else {
                cout << RED << "Invalid Option! Try again...\n\n" << RESET;
                continueProcess();
            }
            break;
        default:
            cout << RED << "Invalid Option! Try again...\n\n" << RESET;
            continueProcess();
            break;
    }
}