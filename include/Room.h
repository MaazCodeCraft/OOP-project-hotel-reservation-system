#ifndef ROOM_H
#define ROOM_H

#include <string>
using namespace std;

class Room {
private:
    string roomNumber;
    bool isBooked;
    int customerID;
    double roomPrice;
    int roomFloor;

public:
    Room(string number, double price, int floor);

    void setRoomNumber(string number);
    string getRoomNumber() const;

    void setIsBooked(bool booked);
    bool getIsBooked() const;

    void setCustomerID(int customer);
    int getCustomerID() const;

    void setRoomPrice(double price);
    double getRoomPrice() const;

    void setRoomFloor(int floor);
    int getRoomFloor() const;

    void book(int customer);
    void vacate();
    void getDetails() const;
};

#endif