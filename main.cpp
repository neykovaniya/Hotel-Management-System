#include <iostream>
#include "Guest.h"
#include "Room.h"
#include "User.h"
#include "Reservation.h"

const int MAX_ROOMS = 10;
const int MAX_GUESTS = 10;
const int MAX_RESERVATIONS = 10;
const int BUFFER_SIZE = 200;

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
        std::cout << "4. Register new guest" << std::endl;
        std::cout << "5. Create new reservation" << std::endl;
        std::cout << "6. Exit" << std::endl;
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
            //fix validation
            case 4: {
                if (guestCount >= MAX_GUESTS) {
                    std::cout << "No space for more guests :(" << std::endl;
                    break;
                }
                char temp[BUFFER_SIZE];
                char *name = nullptr;
                char *phone = nullptr;
                char *email = nullptr;
                int statusInput;

                std::cin.ignore(); //removing \n

                while (true) {
                    std::cout << "Enter name: ";
                    std::cin.getline(temp, BUFFER_SIZE);
                    try {
                        Guest::nameValidation(temp);
                        name = new char[strlen(temp) + 1];
                        strcpy(name, temp);
                        break;
                    } catch (const std::invalid_argument &e) {
                        std::cout << "Invalid name: " << e.what() << std::endl << std::flush;
                    }
                }

                while (true) {
                    std::cout << "Enter phone (10 digits): ";
                    std::cin.getline(temp, BUFFER_SIZE);
                    try {
                        Guest::phoneValidation(temp);
                        phone = new char[strlen(temp) + 1];
                        strcpy(phone, temp);
                        break;
                    } catch (const std::invalid_argument &e) {
                        std::cout << "Invalid phone: " << e.what() << std::endl;
                    }
                }

                while (true) {
                    std::cout << "Enter email: ";
                    std::cin.getline(temp, BUFFER_SIZE);
                    try {
                        Guest::emailValidation(temp);
                        email = new char[strlen(temp) + 1];
                        strcpy(email, temp);
                        break;
                    } catch (const std::invalid_argument &e) {
                        std::cout << "Invalid email: " << e.what() << std::endl << std::flush;
                    }
                }

                std::cout << "Enter status (0-REGULAR, 1-GOLD, 2-PLATINUM): ";
                std::cin >> statusInput;

                guests[guestCount++] = new Guest(guestCount + 1, name, phone, email,
                                                 static_cast<guestStatus>(statusInput));
                std::cout << "Guest registered successfully :)))" << std::endl;

                delete[] name;
                delete[] phone;
                delete[] email;

                break;
            }
            case 5: {
                if (reservationCount >= MAX_RESERVATIONS) {
                    std::cout << "No space for more reservations :(" << std::endl;
                    break;
                }

                std::cout << "Guests: " << std::endl;
                for (int i = 0; i < guestCount; i++) {
                    std::cout << "ID: " << guests[i]->getID() << " - " << guests[i]->getName() << std::endl;
                }

                int guestID;
                std::cout << "Enter guest ID: ";
                std::cin >> guestID;
                Guest *selectedGuest = nullptr;
                for (int i = 0; i < guestCount; i++) {
                    if (guests[i]->getID() == guestID) {
                        selectedGuest = guests[i];
                        break;
                    }
                }
                if (!selectedGuest) {
                    std::cout << "Invalid guest ID :(" << std::endl;
                    break;
                }

                std::cout << "Available rooms: " << std::endl;
                for (int i = 0; i < roomCount; i++) {
                    if (rooms[i]->getStatus() == AVAILABLE) {
                        std::cout << "Room number: " << rooms[i]->getRoomNum() << std::endl;
                    }
                }

                int roomNum;
                std::cout << "Enter room number: ";
                std::cin >> roomNum;
                Room *selectedRoom = nullptr;
                for (int i = 0; i < roomCount; i++) {
                    if (rooms[i]->getRoomNum() == roomNum && rooms[i]->getStatus() == AVAILABLE) {
                        selectedRoom = rooms[i];
                        break;
                    }
                }
                if (!selectedRoom) {
                    std::cout << "Invalid room number or room is not available :(" << std::endl;
                    break;
                }

                std::cin.ignore();

                char date[BUFFER_SIZE];
                while (true) {
                    std::cout << "Enter check-in date (DD.MM.YYYY): ";
                    std::cin.getline(date, BUFFER_SIZE);
                    try {
                        Reservation::dateValidation(date);
                        break;
                    } catch (const std::invalid_argument &e) {
                        std::cout << "Invalid date: " << e.what() << std::endl;
                    }
                }

                int nights;
                std::cout << "Enter number of nights: ";
                std::cin >> nights;
                if (nights <= 0) {
                    std::cout << "Number of nights must be positive :(" << std::endl;
                    break;
                }

                reservations[reservationCount++] = new Reservation(
                    reservationCount + 1, selectedGuest, selectedRoom, date, nights);
                selectedRoom->setStatus(RESERVED);

                std::cout << "Reservation created successfully :)" << std::endl;
                break;
            }
            case 6:
                std::cout << "Bye bye :)" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Try again :(" << std::endl;
        }
    } while (choice != 6);

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
