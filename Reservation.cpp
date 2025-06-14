#include <fstream>
#include <iostream>
#include <cstring>
#include "Reservation.h"

void Reservation::free() {
    delete[] checkInDate;
    checkInDate = nullptr;
}

void Reservation::copyFrom(const Reservation &other) {
    id = other.id;
    guest = other.guest;
    room = other.room;
    nights = other.nights;
    totalPrice = other.totalPrice;

    checkInDate = new char[strlen(other.checkInDate) + 1];
    strcpy(checkInDate, other.checkInDate);
}

Reservation::Reservation(int _id, Guest *_guest, Room *_room, const char *_checkInDate, int _nights) : id(_id),
    guest(_guest), room(_room), nights(_nights), totalPrice(0.0) {
    dateValidation(_checkInDate);
    checkInDate = new char[strlen(_checkInDate) + 1];
    strcpy(checkInDate, _checkInDate);
    calculateTotalPrice();
}

Reservation::Reservation(const Reservation &other) {
    copyFrom(other);
}

Reservation &Reservation::operator=(const Reservation &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Reservation::~Reservation() {
    free();
}

void Reservation::setDate(const char *_date) {
    dateValidation(_date);
    delete[] checkInDate;
    checkInDate = new char[strlen(_date) + 1];
    strcpy(checkInDate, _date);
}

void Reservation::setNights(int _nights) {
    if (_nights <= 0) {
        throw std::invalid_argument("Nights must be a positive number :(");
    }
    nights = _nights;
    calculateTotalPrice();
}

void Reservation::calculateTotalPrice() {
    if (room) {
        /// occupancyRate = брой заети / общо
        double rate = 0.0;
        if (Room::getNextRoomNum() > 1) {
            int occupied = 0;
            for (int i = 0; i < Room::getNextRoomNum() - 1; i++) {
                // count RESERVED rooms (само за реален масив)
            }
            rate = occupied * 1.0 / (Room::getNextRoomNum() - 1);
        }
        totalPrice = room->getDynamicPrice(checkInDate, rate) * nights;


    } else {
        totalPrice = 0;
    }
}

int Reservation::getID() const {
    return id;
}

Guest *Reservation::getGuest() const {
    return guest;
}

Room *Reservation::getRoom() const {
    return room;
}

const char *Reservation::getCheckInDate() const {
    return checkInDate;
}

int Reservation::getNights() const {
    return nights;
}

double Reservation::getTotalPrice() const {
    return totalPrice;
}

void Reservation::print() const {
    std::cout << "Reservation " << id << std::endl;

    std::cout << "Guest: ";
    if (guest) guest->print();
    std::cout << "Room: ";
    if (room) room->print();
    std::cout << "Check-in date: " << checkInDate << std::endl;
    std::cout << "Nights: " << nights << std::endl;
    std::cout << "Total Price: " << totalPrice << std::endl;
}

void Reservation::dateValidation(const char* _date) {
    if (!_date) {
        throw std::invalid_argument("Date cannot be null :(");
    }
    if (strlen(_date) != 10) {
        throw std::invalid_argument("Date must be in format DD.MM.YYYY :(");
    }
    if (_date[2] != '.' || _date[5] != '.') {
        throw std::invalid_argument("Date must have '.' (DD.MM.YYYY) :(");
    }
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (!(_date[i] >= '0' && _date[i] <= '9')) {
            throw std::invalid_argument("Date must contain digits and '.' :(");
        }
    }
    int day = (_date[0] - '0') * 10 + (_date[1] - '0');
    int month = (_date[3] - '0') * 10 + (_date[4] - '0');
    if (day < 1 || day > 31) {
        throw std::invalid_argument("Day must be between 01 and 31 :(");
    }
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be between 01 and 12 :(");
    }
}
void Reservation::saveToFile(std::ofstream& out) const {
    out << id << '\n'
        << guest->getID() << '\n'
        << room->getRoomNum() << '\n'
        << checkInDate << '\n'
        << nights << '\n';
}

Reservation* Reservation::loadFromFile(std::ifstream& in, Guest* guests[], int guestCount, Room* rooms[], int roomCount) {
    int id, guestID, roomNum, nights;
    char date[200];

    if (!(in >> id)) return nullptr;
    in >> guestID >> roomNum;
    in.ignore();
    in.getline(date, 200);
    in >> nights;
    in.ignore();

    Guest* g = nullptr;
    Room* r = nullptr;

    for (int i = 0; i < guestCount; i++) {
        if (guests[i]->getID() == guestID) {
            g = guests[i];
            break;
        }
    }

    for (int i = 0; i < roomCount; i++) {
        if (rooms[i]->getRoomNum() == roomNum) {
            r = rooms[i];
            break;
        }
    }

    if (!g || !r) return nullptr;

    return new Reservation(id, g, r, date, nights);
}