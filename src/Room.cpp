#include "../include/Room.h"

#include <iostream>

#include "../include/Colors.h"

using namespace std;

Room::Room(string number, double price, int floor) {
    setRoomNumber(number);
    isBooked = false;
    customerID = -1;
    setRoomPrice(price);
    setRoomFloor(floor);
}

void Room::setRoomNumber(string number) { roomNumber = number; }

string Room::getRoomNumber() const { return roomNumber; }

void Room::setIsBooked(bool booked) { isBooked = booked; }

bool Room::getIsBooked() const { return isBooked; }

void Room::setCustomerID(int customer) { customerID = customer; }

int Room::getCustomerID() const { return customerID; }

void Room::setRoomPrice(double price) { roomPrice = price; }

double Room::getRoomPrice() const { return roomPrice; }

void Room::setRoomFloor(int floor) { roomFloor = floor; }

int Room::getRoomFloor() const { return roomFloor; }

void Room::book(int customer) {
    isBooked = true;
    customerID = customer;
}

void Room::vacate() {
    isBooked = false;
    customerID = -1;
}

void Room::getDetails() const {
    cout << "Room No: " << roomNumber << endl;
    cout << "Floor No: " << roomFloor << endl;
    cout << "Price ($): " << roomPrice << endl;
    cout << "Available: " << (isBooked ? "No" : "Yes") << endl;
    if (isBooked) {
        cout << "Booked by Customer ID: " << customerID << endl;
    }
}