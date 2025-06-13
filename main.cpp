#include <iostream>
#include <cstring>
#include "Guest.h"
#include "Room.h"
#include "User.h"
#include "Reservation.h"

const int MAX_ROOMS = 10;
const int MAX_GUESTS = 10;
const int MAX_RESERVATIONS = 10;
const int MAX_USERS = 10;
const int BUFFER_SIZE = 200;

bool safeInputInt(const char *message, int &value) {
    std::cout << message;
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(BUFFER_SIZE, '\n');
        std::cout << "Invalid input! Please enter a number." << std::endl;
        return false;
    }
    std::cin.ignore();
    return true;
}

void showAllRooms(Room *rooms[], int roomCount) {
    std::cout << "----------rooms----------" << std::endl;
    for (int i = 0; i < roomCount; i++) {
        rooms[i]->print();
        std::cout << "-------------------" << std::endl;
    }
}

void showAllGuests(Guest *guests[], int guestCount) {
    std::cout << "----------guests----------" << std::endl;
    for (int i = 0; i < guestCount; i++) {
        guests[i]->print();
        std::cout << "-------------------" << std::endl;
    }
}

void showAllReservations(Reservation *reservations[], int reservationCount) {
    std::cout << "----------reservations----------" << std::endl;
    for (int i = 0; i < reservationCount; i++) {
        reservations[i]->print();
        std::cout << "-------------------" << std::endl;
    }
}

void showAvailableRooms(Room *rooms[], int roomCount) {
    std::cout << "----------available rooms----------" << std::endl;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i]->getStatus() == AVAILABLE) {
            rooms[i]->print();
            std::cout << "-------------------" << std::endl;
        }
    }
}

void registerNewGuest(Guest *guests[], int &guestCount) {
    if (guestCount >= MAX_GUESTS) {
        std::cout << "No space for more guests :(" << std::endl;
        return;
    }

    char temp[BUFFER_SIZE];
    char *name = nullptr, *phone = nullptr, *email = nullptr;
    int statusInput;

    std::cin.ignore();

    while (true) {
        std::cout << "Enter name: ";
        std::cin.getline(temp, BUFFER_SIZE);
        try {
            Guest::nameValidation(temp);
            name = new char[strlen(temp) + 1];
            strcpy(name, temp);
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << "Invalid name: " << e.what() << std::endl;
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
            std::cout << "Invalid email: " << e.what() << std::endl;
        }
    }

    if (!safeInputInt("Enter status (0-REGULAR, 1-GOLD, 2-PLATINUM): ", statusInput)) return;

    guests[guestCount++] = new Guest(guestCount + 1, name, phone, email,
                                     static_cast<guestStatus>(statusInput));

    std::cout << "Guest registered successfully :)))" << std::endl;
    delete[] name;
    delete[] phone;
    delete[] email;
}


void createReservation(Room *rooms[], Guest *guests[], Reservation *reservations[],
                       int roomCount, int guestCount, int &reservationCount) {
    if (reservationCount >= MAX_RESERVATIONS) {
        std::cout << "No space for more reservations :(" << std::endl;
        return;
    }

    std::cout << "Guests:";
    for (int i = 0; i < guestCount; i++) {
        std::cout << "ID: " << guests[i]->getID() << " -> " << guests[i]->getName() << std::endl;
    }

    int guestID;
    if (!safeInputInt("Enter guest ID: ", guestID)) return;
    Guest *selectedGuest = nullptr;
    for (int i = 0; i < guestCount; i++) {
        if (guests[i]->getID() == guestID) {
            selectedGuest = guests[i];
            break;
        }
    }
    if (!selectedGuest) {
        std::cout << "Invalid guest ID :(" << std::endl;
        return;
    }

    std::cout << "Available rooms:";
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i]->getStatus() == AVAILABLE) {
            std::cout << "Room number: " << rooms[i]->getRoomNum() << std::endl;
        }
    }

    int roomNum;
    if (!safeInputInt("Enter room number: ", roomNum)) return;
    Room *selectedRoom = nullptr;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i]->getRoomNum() == roomNum && rooms[i]->getStatus() == AVAILABLE) {
            selectedRoom = rooms[i];
            break;
        }
    }
    if (!selectedRoom) {
        std::cout << "Invalid room number or room is not available :(" << std::endl;
        return;
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
    if (!safeInputInt("Enter number of nights: ", nights)) return;

    if (nights <= 0) {
        std::cout << "Number of nights must be positive :(" << std::endl;
        return;
    }

    reservations[reservationCount++] = new Reservation(
        reservationCount + 1, selectedGuest, selectedRoom, date, nights);
    selectedRoom->setStatus(RESERVED);

    std::cout << "Reservation created successfully :)" << std::endl;
}

void searchGuestByName(Guest *guests[], int guestCount) {
    std::cin.ignore();
    char query[BUFFER_SIZE];
    std::cout << "Enter name to search: ";
    std::cin.getline(query, BUFFER_SIZE);
    bool found = false;
    for (int i = 0; i < guestCount; i++) {
        if (strstr(guests[i]->getName(), query)) {
            guests[i]->print();
            std::cout << "-------------------" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No guests found with that name :(" << std::endl;
    }
}

void searchReservationByDate(Reservation *reservations[], int count) {
    std::cin.ignore();
    char queryDate[BUFFER_SIZE];
    std::cout << "Enter date (DD.MM.YYYY): ";
    std::cin.getline(queryDate, BUFFER_SIZE);
    try {
        Reservation::dateValidation(queryDate);
    } catch (const std::invalid_argument &e) {
        std::cout << "Invalid date: " << e.what() << std::endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strcmp(reservations[i]->getCheckInDate(), queryDate) == 0) {
            reservations[i]->print();
            std::cout << "-------------------" << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No reservations found for this date :(" << std::endl;
    }
}

User *login(User *users[], int userCount) {
    char uname[BUFFER_SIZE];
    char pass[BUFFER_SIZE];
    std::cout << "Username: ";
    std::cin.getline(uname, BUFFER_SIZE);
    std::cout << "Password: ";
    std::cin.getline(pass, BUFFER_SIZE);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i]->getUsername(), uname) == 0 &&
            strcmp(users[i]->getPassword(), pass) == 0) {
            std::cout << "Login successful! Welcome, " << uname << "!" << std::endl;
            return users[i];
        }
    }
    std::cout << "Invalid credentials. Exiting..." << std::endl;
    return nullptr;
}

void printMenu(Role role) {
    std::cout << "----------menu----------" << std::endl;
    switch (role) {
        case MANAGER:
            std::cout << "1. Show all rooms" << std::endl;
            std::cout << "2. Show all guests" << std::endl;
            std::cout << "3. Show all reservations" << std::endl;
            std::cout << "4. Register new guest" << std::endl;
            std::cout << "5. Create new reservation" << std::endl;
            std::cout << "6. Show only available rooms" << std::endl;
            std::cout << "7. Search guest by name" << std::endl;
            std::cout << "8. Search reservations by date" << std::endl;
            std::cout << "9. Exit" << std::endl;
            break;
        case RECEPTIONIST:
            std::cout << "1. Show all rooms" << std::endl;
            std::cout << "2. Show all guests" << std::endl;
            std::cout << "3. Show all reservations" << std::endl;
            std::cout << "4. Register new guest" << std::endl;
            std::cout << "5. Create new reservation" << std::endl;
            std::cout << "6. Show only available rooms" << std::endl;
            std::cout << "7. Search guest by name" << std::endl;
            std::cout << "8. Exit" << std::endl;
            break;
        case ACCOUNTANT:
            std::cout << "1. Show all reservations" << std::endl;
            std::cout << "2. Search reservations by date" << std::endl;
            std::cout << "3. Exit" << std::endl;
            break;
    }
}

int main() {
    Room *rooms[MAX_ROOMS];
    int roomCount = 0;
    rooms[roomCount++] = new Room(roomCount + 1, SINGLE, AVAILABLE, 80.0);
    rooms[roomCount++] = new Room(roomCount + 1, DELUXE, RESERVED, 150.0);
    rooms[roomCount++] = new Room(roomCount + 1, APARTMENT, AVAILABLE, 200.0);

    Guest *guests[MAX_GUESTS];
    int guestCount = 0;
    guests[guestCount++] = new Guest(1, "Niya", "0888123456", "niya@gmail.com", GOLD);
    guests[guestCount++] = new Guest(2, "Dari", "0888777666", "dari@gmail.com", REGULAR);

    Reservation *reservations[MAX_RESERVATIONS];
    int reservationCount = 0;
    reservations[reservationCount++] = new Reservation(1, guests[0], rooms[0], "01.06.2025", 2);
    reservations[reservationCount++] = new Reservation(2, guests[1], rooms[2], "05.06.2025", 3);

    User *users[MAX_USERS];
    int userCount = 0;
    users[userCount++] = new User("admin", "admin123", MANAGER);
    users[userCount++] = new User("reception", "recept123", RECEPTIONIST);
    users[userCount++] = new User("account", "money$123", ACCOUNTANT);

    User *currentUser = login(users, userCount);
    if (!currentUser) return 1;

    int choice;
    do {
        printMenu(currentUser->getRole());
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(BUFFER_SIZE, '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }


        switch (currentUser->getRole()) {
            case MANAGER:
                switch (choice) {
                    case 1: showAllRooms(rooms, roomCount);
                        break;
                    case 2: showAllGuests(guests, guestCount);
                        break;
                    case 3: showAllReservations(reservations, reservationCount);
                        break;
                    case 4: registerNewGuest(guests, guestCount);
                        break;
                    case 5: createReservation(rooms, guests, reservations, roomCount, guestCount, reservationCount);
                        break;
                    case 6: showAvailableRooms(rooms, roomCount);
                        break;
                    case 7: searchGuestByName(guests, guestCount);
                        break;
                    case 8: searchReservationByDate(reservations, reservationCount);
                        break;
                    case 9: std::cout << "Bye bye :)";
                        break;
                    default: std::cout << "Invalid choice";
                        break;
                }
                break;
            case RECEPTIONIST:
                switch (choice) {
                    case 1: showAllRooms(rooms, roomCount);
                        break;
                    case 2: showAllGuests(guests, guestCount);
                        break;
                    case 3: showAllReservations(reservations, reservationCount);
                        break;
                    case 4: registerNewGuest(guests, guestCount);
                        break;
                    case 5: createReservation(rooms, guests, reservations, roomCount, guestCount, reservationCount);
                        break;
                    case 6: showAvailableRooms(rooms, roomCount);
                        break;
                    case 7: searchGuestByName(guests, guestCount);
                        break;
                    case 8: std::cout << "Bye bye :)";
                        break;
                    default: std::cout << "Invalid choice";
                        break;
                }
                break;
            case ACCOUNTANT:
                switch (choice) {
                    case 1: showAllReservations(reservations, reservationCount);
                        break;
                    case 2: searchReservationByDate(reservations, reservationCount);
                        break;
                    case 3: std::cout << "Bye bye :)";
                        break;
                    default: std::cout << "Invalid choice";
                        break;
                }
                break;
        }
    } while (!((currentUser->getRole() == MANAGER && choice == 9) ||
               (currentUser->getRole() == RECEPTIONIST && choice == 8) ||
               (currentUser->getRole() == ACCOUNTANT && choice == 3)));

    for (int i = 0; i < roomCount; i++) delete rooms[i];
    for (int i = 0; i < guestCount; i++) delete guests[i];
    for (int i = 0; i < reservationCount; i++) delete reservations[i];
    for (int i = 0; i < userCount; i++) delete users[i];

    return 0;
}
