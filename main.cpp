#include <iostream>
#include "Guest.h"
#include "Room.h"
#include "User.h"
#include "Reservation.h"

const int MAX_ROOMS = 10;

int main() {
    Room *rooms[MAX_ROOMS];
    int roomCount = 0;
    rooms[roomCount++] = new Room(1, SINGLE, AVAILABLE, 80.0);
    rooms[roomCount++] = new Room(2, DELUXE, RESERVED, 150.0);
    rooms[roomCount++] = new Room(3, APARTMENT, AVAILABLE, 200.0);

    std::cout << "----------rooms----------" << std::endl;
    for (int i = 0; i < roomCount; ++i) {
        rooms[i]->print();
        std::cout << "--------------------------" << std::endl;
    }

    for (int i = 0; i < roomCount; ++i) {
        delete rooms[i];
    }

    return 0;
}
