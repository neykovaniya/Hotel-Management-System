#include <iostream>
#include "Guest.h"
#include "Room.h"
#include "User.h"
#include "Reservation.h"

const int MAX_ROOMS = 10;
const int MAX_GUESTS = 10;

int main() {
    Room *rooms[MAX_ROOMS];
    int roomCount = 0;
    rooms[roomCount++] = new Room(1, SINGLE, AVAILABLE, 80.0);
    rooms[roomCount++] = new Room(2, DELUXE, RESERVED, 150.0);
    rooms[roomCount++] = new Room(3, APARTMENT, AVAILABLE, 200.0);

    Guest *guests[MAX_GUESTS];
    int guestCount = 0;
    guests[guestCount++] = new Guest(1, "Niya", "0888123456", "niya@gmail.com", GOLD);
    guests[guestCount++] = new Guest(2, "Dari", "0888777666", "dari@gmail.com", REGULAR);

    std::cout << "----------rooms----------" << std::endl;
    for (int i = 0; i < roomCount; i++) {
        rooms[i]->print();
        std::cout << "--------------------------" << std::endl;
    }

    for (int i = 0; i < roomCount; i++) {
        delete rooms[i];
    }
    std::cout << "----------guests----------" << std::endl;
    for (int i = 0; i < guestCount; i++) {
        guests[i]->print();
        std::cout << "--------------------------" << std::endl;
    }
    for (int i = 0; i < guestCount; i++) {
        delete guests[i];
    }
    return 0;
}