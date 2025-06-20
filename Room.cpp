#include <fstream>
#include <iostream>
#include "Room.h"
int Room::nextRoomNum = 1;

Room::Room(roomType _type, roomStatus _status, double _price)
    : roomNum(nextRoomNum++), type(_type), status(_status), price(_price) {
}

Room::Room(int _roomNum, roomType _type, roomStatus _status, double _price)
    : roomNum(_roomNum), type(_type), status(_status), price(_price) {
    if (_roomNum >= nextRoomNum) {
        nextRoomNum = _roomNum + 1;
    }
}

void Room::setStatus(roomStatus _status) {
    status = _status;
}

void Room::setPrice(double _price) {
    if (_price < 0) {
        throw std::invalid_argument("Price cannot be negative :(");
    }
    price = _price;
}

int Room::getRoomNum() const {
    return roomNum;
}

roomType Room::getType() const {
    return type;
}

roomStatus Room::getStatus() const {
    return status;
}

double Room::getPricePerNight() const {
    return price;
}

void Room::print() const {
    std::cout << "Room " << roomNum << std::endl;
    std::cout << "Type: ";
    switch (type) {
        case SINGLE:
            std::cout << "Single";
            break;
        case DOUBLE:
            std::cout << "Double";
            break;
        case DELUXE:
            std::cout << "Deluxe";
            break;
        case CONFERENCE_HALL:
            std::cout << "Conference Hall";
            break;
        case APARTMENT:
            std::cout << "Apartment";
            break;
    }
    std::cout << std::endl << "Status: ";
    switch (status) {
        case AVAILABLE:
            std::cout << "Available";
            break;
        case RESERVED:
            std::cout << "Reserved";
            break;
        case UNDER_MAINTENANCE:
            std::cout << "Under Maintenance";
            break;
    }
    std::cout << std::endl << "Price: " << price << std::endl;
}

void Room::saveToFile(std::ofstream &out) const {
    out << roomNum << '\n'
            << type << '\n'
            << status << '\n'
            << price << '\n';
}

Room *Room::loadFromFile(std::ifstream &in) {
    int number, typeInt, statusInt;
    double price;

    if (!(in >> number)) return nullptr;
    in >> typeInt >> statusInt >> price;
    in.ignore();
    return new Room(number, static_cast<roomType>(typeInt), static_cast<roomStatus>(statusInt), price);
}

double Room::getDynamicPrice(const char *dateStr, double occupancyRate) const {
    double finalPrice = price;

    int month = (dateStr[3] - '0') * 10 + (dateStr[4] - '0');
    if (month >= 6 && month <= 8) {
        finalPrice *= 1.2;
    }

    if (occupancyRate > 0.7) {
        finalPrice *= 1.15;
    }

    return finalPrice;
}

int Room::getNextRoomNum() {
    return nextRoomNum;
}

Room* Room::clone() const {
    return new Room(roomNum, type, status, price);
}