#include <fstream>
#include <iostream>
#include <cstring>
#include "Reservation.h"

const int MAX_SIZE = 200;
void Reservation::free() {
    delete[] checkInDate;
    checkInDate = nullptr;

    delete guest;
    delete room;
    guest = nullptr;
    room = nullptr;
}

void Reservation::copyFrom(const Reservation &other) {
    id = other.id;
    nights = other.nights;
    totalPrice = other.totalPrice;

    checkInDate = new char[strlen(other.checkInDate) + 1];
    strcpy(checkInDate, other.checkInDate);

    guest = other.guest ? other.guest->clone() : nullptr;
    room = other.room ? other.room->clone() : nullptr;
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

//редактирано
void Reservation::calculateTotalPrice() {
    if (room) {
        double rate = 0.3; //фиксирана заетост
        double basePrice = room->getDynamicPrice(checkInDate, rate) * nights;
        if (guest) {
            switch (guest->getStatus()) {
                case GOLD:
                    basePrice *= 0.90;
                    break;
                case PLATINUM:
                    basePrice *= 0.80;
                    break;
                default:
                    break;
            }
        }

        totalPrice = basePrice;
    } else {
        totalPrice = 0;
    }
}

void Reservation::calculateTotalPrice(Room *rooms[], int roomCount) {
    if (!room) {
        totalPrice = 0;
        return;
    }

    double occupancyRate = 0.0;
    if (roomCount > 0) {
        int reserved = 0;
        for (int i = 0; i < roomCount; ++i)
            if (rooms[i]->getStatus() == RESERVED) reserved++;
        occupancyRate = reserved * 1.0 / roomCount;
    }

    double basePrice = room->getDynamicPrice(checkInDate, occupancyRate) * nights;

    if (guest) {
        switch (guest->getStatus()) {
            case GOLD: basePrice *= 0.90;
                break;
            case PLATINUM: basePrice *= 0.80;
                break;
            default: break;
        }
    }

    totalPrice = basePrice;
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
    double rate = 0.0;
    if (Room::getNextRoomNum() > 1) {
        int occupied = 0;
        for (int i = 0; i < Room::getNextRoomNum() - 1; i++) {
        }
        rate = occupied * 1.0 / (Room::getNextRoomNum() - 1);
    }
    double dynamicPrice = 0.0;
    dynamicPrice = room->getDynamicPrice(checkInDate, rate) * nights;
    std::cout << "Base Price (w/o discount): " << dynamicPrice << std::endl;

    if (guest) {
        double discount = 0.0;
        switch (guest->getStatus()) {
            case GOLD:
                discount = 0.10;
                break;
            case PLATINUM:
                discount = 0.20;
                break;
            default:
                break;
        }
        if (discount > 0.0) {
            std::cout << "Applied Discount: " << (discount * 100) << "%" << std::endl;
        }
    }

    std::cout << "Total Price: " << totalPrice << std::endl;
}


//редактирано
void Reservation::dateValidation(const char *_date) {
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

    int day   = (_date[0] - '0') * 10 + (_date[1] - '0');
    int month = (_date[3] - '0') * 10 + (_date[4] - '0');
    int year  = (_date[6] - '0') * 1000 + (_date[7] - '0') * 100 +
                (_date[8] - '0') * 10 + (_date[9] - '0');

    if (month < 1 || month > 12) {
        throw std::invalid_argument("Month must be between 01 and 12 :(");
    }

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                          31, 31, 30, 31, 30, 31 };

    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (isLeap && month == 2) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        throw std::invalid_argument("Invalid day for this month :(");
    }
}


void Reservation::saveToFile(std::ofstream &out) const {
    out << id << '\n'
            << guest->getID() << '\n'
            << room->getRoomNum() << '\n'
            << checkInDate << '\n'
            << nights << '\n'
            << totalPrice << '\n';
}

Reservation *Reservation::loadFromFile(std::ifstream &in, Guest *guests[], int guestCount, Room *rooms[],
                                       int roomCount) {
    int id, guestID, roomNum, nights;
    char date[MAX_SIZE];

    if (!(in >> id)) return nullptr;
    in >> guestID >> roomNum;
    in.ignore();
    in.getline(date, MAX_SIZE);
    in >> nights;
    in.ignore();
    double savedPrice;
    in >> savedPrice;
    in.ignore();
    Guest *g = nullptr;
    Room *r = nullptr;

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
