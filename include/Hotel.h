#ifndef HOTEL_H
#define HOTEL_H

#include <string>
#include <vector>

#include "Customer.h"
#include "Room.h"
using namespace std;

class Hotel {
private:
    string hotelName;
    vector<Room> rooms;
    int totalFloors;
    int eachFloorRoomCount;

public:
    Hotel(const string &name, int floors, int roomEach, double price);

    void setHotelName(const string &name);
    string getHotelName() const;

    void setTotalFloors(int floors);
    int getTotalFloors() const;

    void setEachFloorRoomCount(int roomEach);
    int getEachFloorRoomCount() const;

    bool isRoomAvailable(const string &roomNumber) const;
    bool bookRoom(const string &roomNumber, Customer &customer);
    void vacateRoom(const string &roomNumber);
    double getRoomPrice(const string &roomNumber) const;
    int checkRoom(const string &roomNumber) const;
    bool editRoom(const string &roomNumber);
    void viewAllRooms() const;
};

#endif