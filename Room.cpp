//
// Created by Niya Neykova on 24.05.25.
//
#include <iostream>
#include "Room.h"
int Room::nextRoomNum = 1;
Room::Room(roomType _type, roomStatus _status, double _price)
    : roomNum(nextRoomNum++), type(_type), status(_status), price(_price) {
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
