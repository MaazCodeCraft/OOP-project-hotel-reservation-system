#include "../include/Hotel.h"

#include <iostream>

#include "../include/Colors.h"

using namespace std;

Hotel::Hotel(const string& name, int floors, int roomEach, double price) {
    setHotelName(name);
    setTotalFloors(floors);
    setEachFloorRoomCount(roomEach);

    char floorChar = 'A';
    int floorExt = 1;
    for (int floor = 1; floor <= totalFloors; ++floor) {
        for (int roomNum = 1; roomNum <= eachFloorRoomCount; ++roomNum) {
            string roomNumber = floorChar + to_string(floorExt) +
                                (roomNum < 10 ? "00" : (roomNum < 100 ? "0" : "")) +
                                to_string(roomNum);
            rooms.push_back(Room(roomNumber, price, floor));
        }
        if (floorChar == 'Z') {
            floorChar = 'A';
            floorExt++;
        } else {
            floorChar++;
        }
    }
}

void Hotel::setHotelName(const string& name) { hotelName = name; }

string Hotel::getHotelName() const { return hotelName; }

void Hotel::setTotalFloors(int floors) { totalFloors = floors; }

int Hotel::getTotalFloors() const { return totalFloors; }

void Hotel::setEachFloorRoomCount(int roomEach) { eachFloorRoomCount = roomEach; }

int Hotel::getEachFloorRoomCount() const { return eachFloorRoomCount; }

bool Hotel::isRoomAvailable(const string& roomNumber) const {
    for (const auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber && !room.getIsBooked()) {
            return true;
        }
    }
    return false;
}

bool Hotel::bookRoom(const string& roomNumber, Customer& customer) {
    for (auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber && !room.getIsBooked()) {
            room.book(customer.getCustomerID());
            cout << GREEN << "Room " << roomNumber << " Booked For " << customer.getCustomerName()
                 << RESET << endl;
            cout << "\a";
            return true;
        }
    }
    cout << RED << "Room " << roomNumber << " Is Not Available!" << RESET << endl;
    return false;
}

void Hotel::vacateRoom(const string& roomNumber) {
    for (auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            if (room.getIsBooked()) {
                room.vacate();
                cout << GREEN << "Room " << roomNumber << " Vacated!" << RESET << endl;
                cout << "\a";
            } else {
                cout << GREEN << "Room " << roomNumber << " Is Available To Book!" << RESET << endl;
            }
            return;
        }
    }
    cout << RED << "Room " << roomNumber << " Doesn't Exist!" << RESET << endl;
}

double Hotel::getRoomPrice(const string& roomNumber) const {
    for (const auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            return room.getRoomPrice();
        }
    }
    cout << RED << "Room " << roomNumber << " Doesn't Exist!" << RESET << endl;
    return -1;
}

int Hotel::checkRoom(const string& roomNumber) const {
    for (const auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            room.getDetails();
            return room.getCustomerID();
        }
    }
    cout << RED << "Room " << roomNumber << " Doesn't Exist!" << RESET << endl;
    return -1;
}

bool Hotel::editRoom(const string& roomNumber) {
    for (auto& room : rooms) {
        if (room.getRoomNumber() == roomNumber) {
            double price;
            cout << "New Price ($): ";
            while (!(cin >> price) || price < 0) {
                cin.clear();
                cout << RED << "Invalid input. Please enter a positive price." << RESET << endl;
                cout << "New Price ($): ";
            }
            room.setRoomPrice(price);
            cout << GREEN << "Room " << roomNumber << " Price Updated To " << price << RESET
                 << endl;
            return true;
        }
    }
    cout << RED << "Room " << roomNumber << " Doesn't Exist!" << RESET << endl;
    return false;
}

void Hotel::viewAllRooms() const {
    char floorChar = 'A';
    int floorExt = 1;
    for (int floor = 1; floor <= totalFloors; ++floor) {
        cout << "FLOOR " << (floor < 10 ? "00" : (floor < 100 ? "0" : "")) << floor
             << ":\n----------\n";
        for (int roomNum = 1; roomNum <= eachFloorRoomCount; ++roomNum) {
            string roomNumber = floorChar + to_string(floorExt) +
                                (roomNum < 10 ? "00" : (roomNum < 100 ? "0" : "")) +
                                to_string(roomNum);
            if (isRoomAvailable(roomNumber)) {
                cout << "[" << GREEN << roomNumber << RESET << "] ";
            } else {
                cout << "[" << RED << roomNumber << RESET << "] ";
            }
        }
        cout << endl << endl;
        if (floorChar == 'Z') {
            floorChar = 'A';
            floorExt++;
        } else {
            floorChar++;
        }
    }
    cout << endl;
}