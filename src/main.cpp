#include <iostream>
#include <string>
#include <vector>

#include "../include/Admin.h"
#include "../include/Colors.h"
#include "../include/Customer.h"
#include "../include/Hotel.h"
#include "../include/Utils.h"

using namespace std;

int main() {
    bool loggedIn = false;
    string hotelName;
    string hotelAddress;
    int totalFloors;
    int roomsPerFloor;
    double defaultRoomCost;

    // Intro Screen
    cout << "=========================================" << endl;
    cout << BOLD << BG_GREEN << "|| Hotel Reservation Management System ||" << RESET << endl;
    cout << "=========================================" << endl << endl;
    cout << "This Management System is developed as a project of the course -" << YELLOW << "OOP\n"
         << RESET;
    cout << "Given by our honerable Professor - [" << YELLOW << "Irfan Ullah Khan" << RESET
         << "]\n\n";
    cout << BOLD << BG_BRIGHT_CYAN << BLACK << "DESCRIPTION:" << RESET << "\n-----------\n";
    cout << RED
         << "A complete solution to manage your hotel with multiple admins and a super admin. "
            "Where only the super admin"
            " can add new admins. All admins can manage the rooms, book a room for the customers, "
            "check all rooms, "
            "edit price of the rooms, add new customers, and vacate a room when customers leave! "
            "\n\n"
         << RESET;
    cout << BOLD << BG_BRIGHT_CYAN << BLACK << "DEVELOPED BY:" << RESET << "\n-----------\n";
    cout << "Student of Lahor Degree College Lahor Swabi";
    cout << "\n[NAME:" << BLUE << " Maaz Ur Rahman" << RESET << ", ID:" << BLUE << " CS-23/302"
         << RESET << "]\n"
         << endl;
    cout << "\nYou are just one step away from having your hotel management system!";
    cout << RED << "\nPress Enter To Continue..." << RESET;
    cin.get();
    system("cls");

    // First Time Hotel Setup
    cout << BLUE
         << "Before we can continue, let's setup your hotel first. "
            "Please fill the form below:\n\n"
         << RESET;

    do {
        cout << "Hotel Name: ";
        getline(cin, hotelName);
        if (hotelName.empty()) {
            cout << RED << "Hotel name cannot be empty. Please enter the hotel name.\n" << RESET;
        }
    } while (hotelName.empty());

    do {
        cout << "Hotel Address: ";
        getline(cin, hotelAddress);
        if (hotelAddress.empty()) {
            cout << RED << "Hotel address cannot be empty. Please enter the hotel address.\n"
                 << RESET;
        }
    } while (hotelAddress.empty());

    do {
        cout << "Total Floors: ";
        cin >> totalFloors;
        if (cin.fail() || totalFloors <= 0) {
            cout << RED << "Total floors must be a positive number. Please enter a valid number.\n"
                 << RESET;
            invalid_input();
        }
    } while (totalFloors <= 0);

    do {
        cout << "Rooms In Each Floor: ";
        cin >> roomsPerFloor;
        if (cin.fail() || roomsPerFloor <= 0) {
            cout << RED
                 << "Rooms per floor must be a positive number. Please enter a valid number.\n"
                 << RESET;
            invalid_input();
        }
    } while (roomsPerFloor <= 0);

    do {
        cout << YELLOW << "Default Room Cost ($): " << RESET;
        cin >> defaultRoomCost;
        if (cin.fail() || defaultRoomCost <= 0) {
            cout << RED
                 << "Default room cost must be a positive number. Please enter a valid number.\n"
                 << RESET;
            invalid_input();
        }
    } while (defaultRoomCost <= 0);

    cout << endl;

    Hotel hotel(hotelName, totalFloors, roomsPerFloor, defaultRoomCost);
    vector<Customer> customers;
    cout << GREEN << "Hotel Information Saved!" << RESET;
    continueProcess();

    cout << GREEN << "Hotel Information!" << RESET << endl;
    cout << "\nHotel Name entered: " << MAGENTA << hotelName << RESET << endl;
    cout << "Hotel Address entered: " << MAGENTA << hotelAddress << RESET << endl;
    cout << "Total Floors entered: " << MAGENTA << totalFloors << RESET << endl;
    cout << "Rooms In Each Floor entered: " << MAGENTA << roomsPerFloor << RESET << endl;
    cout << "Default Room Cost entered: " << MAGENTA << defaultRoomCost << "$" << RESET << endl;
    continueProcess();

    // Super Admin Setup
    cout << CYAN << "Super Admin\n=================\n" << RESET << endl;
    cout << "Let's setup a super admin of your hotel. Only super admins have the power to"
            " add more admins and have all admin powers\n\n";
    vector<Admin> admins;
    admins.push_back(Admin(true));
    cout << "\nSuper Admin created! Now continue to the panel using your username "
            "and password to start managing your hotel";
    continueProcess();

    // Admin Panel
    while (true) {
        if (::loggedIn) {
            menuScreen(admins, customers, hotel);
        } else {
            if (loginScreen(admins)) {
                ::loggedIn = true;
            } else {
                system("cls");
                cout << RED << "Invalid Login Credentials!" << RESET;
            }
        }
    }
    return 0;
}