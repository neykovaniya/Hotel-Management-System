#include <iostream>
#include "Guest.h"
#include "Room.h"
#include "User.h"
#include "Reservation.h"

const int MAX_ROOMS = 10;
const int MAX_GUESTS = 10;
const int MAX_RESERVATIONS = 10;

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

    Reservation *reservations[MAX_RESERVATIONS];
    int reservationCount = 0;
    reservations[reservationCount++] = new Reservation(1, guests[0], rooms[0], "01.06.2025", 2);
    reservations[reservationCount++] = new Reservation(2, guests[1], rooms[2], "05.06.2025", 3);

    int choice;
    do {
        std::cout << "----------menu----------" << std::endl;
        std::cout << "1. Show all rooms" << std::endl;
        std::cout << "2. Show all guests" << std::endl;
        std::cout << "3. Show all reservations" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "----------rooms----------" << std::endl;
                for (int i = 0; i < roomCount; i++) {
                    rooms[i]->print();
                    std::cout << "-------------------" << std::endl;
                }
                break;
            case 2:
                std::cout << "----------guests----------" << std::endl;
                for (int i = 0; i < guestCount; i++) {
                    guests[i]->print();
                    std::cout << "-------------------" << std::endl;
                }
                break;
            case 3:
                std::cout << "----------reservations----------" << std::endl;
                for (int i = 0; i < reservationCount; i++) {
                    reservations[i]->print();
                    std::cout << "-------------------" << std::endl;
                }
                break;
            case 4:
                std::cout << "Bye bye :)" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again :(" << std::endl;
        }
    } while (choice != 4);

    for (int i = 0; i < roomCount; i++) {
        delete rooms[i];
    }

    for (int i = 0; i < guestCount; i++) {
        delete guests[i];
    }

    for (int i = 0; i < reservationCount; i++) {
        delete reservations[i];
    }

    return 0;
}
