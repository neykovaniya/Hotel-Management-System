#include <iostream>
#include <cstring>
#include <fstream>
#include "Guest.h"
#include "Room.h"
#include "User.h"
#include "Reservation.h"

template<typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

const int MAX_ROOMS = 10;
const int MAX_GUESTS = 10;
const int MAX_RESERVATIONS = 10;
const int MAX_USERS = 10;
const int BUFFER_SIZE = 200;

// int toIntDate(const char* date) {
//     return (date[6] - '0') * 1000000 + (date[7] - '0') * 100000 +
//            (date[8] - '0') * 10000 + (date[3] - '0') * 1000 +
//            (date[4] - '0') * 100 + (date[0] - '0') * 10 + (date[1] - '0');
// }
//
// bool isRoomAvailable(Room* room, const char* newDate, int newNights, Reservation* reservations[], int reservationCount) {
//     int newStart = toIntDate(newDate);
//     int newEnd = newStart + newNights;
//
//     for (int i = 0; i < reservationCount; i++) {
//         if (reservations[i]->getRoom()->getRoomNum() == room->getRoomNum()) {
//             int existingStart = toIntDate(reservations[i]->getCheckInDate());
//             int existingEnd = existingStart + reservations[i]->getNights();
//
//             if (!(newEnd <= existingStart || newStart >= existingEnd)) {
//                 return false;
//             }
//         }
//     }
//     return true;
// }

void generateRevenueAndOccupancyByRoomType(Reservation *reservations[], int reservationCount) {
    const int ROOM_TYPE_COUNT = 5;
    double revenueByType[ROOM_TYPE_COUNT] = {};
    int reservationCountByType[ROOM_TYPE_COUNT] = {};

    for (int i = 0; i < reservationCount; i++) {
        Room *r = reservations[i]->getRoom();
        roomType type = r->getType();
        revenueByType[type] += reservations[i]->getTotalPrice();
        reservationCountByType[type]++;
    }

    const char *typeNames[ROOM_TYPE_COUNT] = {
        "SINGLE", "DOUBLE", "DELUXE", "CONFERENCE_HALL", "APARTMENT"
    };

    std::ofstream out("room_report.txt");
    if (!out) {
        std::cout << "Could not open room_report.txt"<<std::endl;
        return;
    }

    std::cout << "\n--- Revenue and Occupancy by Room Type ---\n";
    out << "--- Revenue and Occupancy by Room Type ---"<<std::endl;
    for (int i = 0; i < ROOM_TYPE_COUNT; i++) {
        std::cout << typeNames[i] << ": " << revenueByType[i] << " BGN, "
                << reservationCountByType[i] << " reservations"<<std::endl;
        out << typeNames[i] << ": " << revenueByType[i] << " BGN, "
                << reservationCountByType[i] << " reservations"<<std::endl;
    }
    out.close();
}

void generateRevenueReportByDate(Reservation *reservations[], int reservationCount) {
    const int MAX_UNIQUE_DATES = 500;
    const int DATE_LENGTH = 11;
    const int MONTH_LENGTH = 8;
    const int YEAR_LENGTH = 5;
    const int MAX_ROOMS_REPORT = 100;
    char uniqueDays[MAX_UNIQUE_DATES][DATE_LENGTH] = {};
    char uniqueMonths[MAX_UNIQUE_DATES][MONTH_LENGTH] = {};
    char uniqueYears[MAX_UNIQUE_DATES][YEAR_LENGTH] = {};
    double revenuePerDay[MAX_UNIQUE_DATES] = {};
    double revenuePerMonth[MAX_UNIQUE_DATES] = {};
    double revenuePerYear[MAX_UNIQUE_DATES] = {};
    int dayCount = 0, monthCount = 0, yearCount = 0;

    for (int i = 0; i < reservationCount; i++) {
        const char *date = reservations[i]->getCheckInDate();
        double price = reservations[i]->getTotalPrice();

        bool foundDay = false;
        for (int j = 0; j < dayCount; j++) {
            if (strcmp(uniqueDays[j], date) == 0) {
                revenuePerDay[j] += price;
                foundDay = true;
                break;
            }
        }
        if (!foundDay && dayCount < MAX_UNIQUE_DATES) {
            strcpy(uniqueDays[dayCount], date);
            revenuePerDay[dayCount++] = price;
        }

        char month[MONTH_LENGTH] = {};
        strncpy(month, date + 3, MONTH_LENGTH-1);
        bool foundMonth = false;
        for (int j = 0; j < monthCount; j++) {
            if (strcmp(uniqueMonths[j], month) == 0) {
                revenuePerMonth[j] += price;
                foundMonth = true;
                break;
            }
        }
        if (!foundMonth && monthCount < MAX_UNIQUE_DATES) {
            strcpy(uniqueMonths[monthCount], month);
            revenuePerMonth[monthCount++] = price;
        }

        char year[YEAR_LENGTH] = {};
        strncpy(year, date + 6, YEAR_LENGTH - 1);
        bool foundYear = false;
        for (int j = 0; j < yearCount; j++) {
            if (strcmp(uniqueYears[j], year) == 0) {
                revenuePerYear[j] += price;
                foundYear = true;
                break;
            }
        }
        if (!foundYear && yearCount < MAX_UNIQUE_DATES) {
            strcpy(uniqueYears[yearCount], year);
            revenuePerYear[yearCount++] = price;
        }
    }

    std::ofstream report("report.txt");
    if (!report.is_open()) {
        std::cout << "Could not open report.txt for writing :(";
        return;
    }

    std::cout << "\n--- Revenue by Day ---\n";
    report << "--- Revenue by Day ---"<<std::endl;
    for (int i = 0; i < dayCount; i++) {
        std::cout << uniqueDays[i] << ": " << revenuePerDay[i] << " BGN"<<std::endl;
        report << uniqueDays[i] << ": " << revenuePerDay[i] << " BGN"<<std::endl;
    }

    std::cout << "\n--- Revenue by Month ---\n";
    report << "\n--- Revenue by Month ---\n";
    for (int i = 0; i < monthCount; i++) {
        std::cout << uniqueMonths[i] << ": " << revenuePerMonth[i] << " BGN"<<std::endl;
        report << uniqueMonths[i] << ": " << revenuePerMonth[i] << " BGN"<<std::endl;
    }

    std::cout << "\n--- Revenue by Year ---\n";
    report << "\n--- Revenue by Year ---\n";
    for (int i = 0; i < yearCount; i++) {
        std::cout << uniqueYears[i] << ": " << revenuePerYear[i] << " BGN" <<std::endl;
        report << uniqueYears[i] << ": " << revenuePerYear[i] << " BGN"<<std::endl;
    }

    report.close();
    int roomNums[MAX_ROOMS_REPORT] = {};
    double roomRevenues[MAX_ROOMS_REPORT] = {};
    int roomCount = 0;

    for (int i = 0; i < reservationCount; i++) {
        int currentRoom = reservations[i]->getRoom()->getRoomNum();
        double price = reservations[i]->getTotalPrice();
        bool found = false;
        for (int j = 0; j < roomCount; j++) {
            if (roomNums[j] == currentRoom) {
                roomRevenues[j] += price;
                found = true;
                break;
            }
        }
        if (!found) {
            roomNums[roomCount] = currentRoom;
            roomRevenues[roomCount] = price;
            roomCount++;
        }
    }

    for (int i = 0; i < roomCount - 1; i++) {
        for (int j = i + 1; j < roomCount; j++) {
            if (roomRevenues[j] > roomRevenues[i]) {
                mySwap(roomRevenues[i], roomRevenues[j]);
                mySwap(roomNums[i], roomNums[j]);
            }
        }
    }

    std::cout << "\n--- Top Earning Rooms ---\n";
    report << "\n--- Top Earning Rooms ---\n";
    for (int i = 0; i < roomCount; i++) {
        std::cout << "Room " << roomNums[i] << ": " << roomRevenues[i] << " BGN"<<std::endl;
        report << "Room " << roomNums[i] << ": " << roomRevenues[i] << " BGN"<<std::endl;
    }
}

void logAction(const char *username, const char *actionDetail, int value1 = -1, int value2 = -1) {
    std::ofstream log("log.txt", std::ios::app);
    if (!log.is_open()) return;

    log << "[" << username << "] " << actionDetail;
    if (value1 != -1) log << " " << value1;
    if (value2 != -1) log << " " << value2;
    log << '\n';

    log.close();
}


void addRoom(Room *rooms[], int &roomCount, User *currentUser) {
    const int ROOM_TYPE_MIN = 0;
    const int ROOM_TYPE_MAX = 4;
    const int INPUT_BUFFER_SIZE = 200;
    if (roomCount >= MAX_ROOMS) {
        std::cout << "No space for more rooms :(" << std::endl;
        return;
    }

    int typeInput;
    while (true) {
        std::cout << "Select room type:" << std::endl;
        std::cout << "0 - SINGLE\n1 - DOUBLE\n2 - DELUXE\n3 - CONFERENCE_HALL\n4 - APARTMENT" << std::endl;
        std::cin >> typeInput;

        if (!std::cin.fail() && typeInput >= ROOM_TYPE_MIN && typeInput <= ROOM_TYPE_MAX) break;

        std::cin.clear();
        std::cin.ignore(INPUT_BUFFER_SIZE, '\n');
        std::cout << "Invalid room type :(. Try again!" << std::endl;
    }

    double price;
    while (true) {
        std::cout << "Enter price per night: ";
        std::cin >> price;

        if (!std::cin.fail() && price >= 0) break;

        std::cin.clear();
        std::cin.ignore(INPUT_BUFFER_SIZE, '\n');
        std::cout << "Invalid price :(. Try again!" << std::endl;
    }

    rooms[roomCount++] = new Room(static_cast<roomType>(typeInput), AVAILABLE, price);
    std::cout << "Room added successfully :)" << std::endl;
    logAction(currentUser->getUsername(), "Added new room");
}


void editReservation(Reservation *reservations[], int reservationCount,
                     Room *rooms[], int roomCount, User *currentUser) {
    while (true) {
        int id;
        std::cout << "Enter reservation ID to edit: ";
        std::cin >> id;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(200, '\n');
            std::cout << "Invalid input :(. Try again!\n" << std::endl;
            continue;
        }

        Reservation *r = nullptr;
        for (int i = 0; i < reservationCount; i++) {
            if (reservations[i]->getID() == id) {
                r = reservations[i];
                break;
            }
        }

        if (!r) {
            std::cout << "Reservation not found :(. Try again!\n" << std::endl;
            continue;
        }

        char newDate[200];
        std::cin.ignore();
        std::cout << "Enter new check-in date (DD.MM.YYYY): ";
        std::cin.getline(newDate, 200);

        try {
            Reservation::dateValidation(newDate);
            r->setDate(newDate);
        } catch (const std::invalid_argument &e) {
            std::cout << "Invalid date: " << e.what() << "\nTry again!\n" << std::endl;
            continue;
        }

        int nights;
        std::cout << "Enter new number of nights: ";
        std::cin >> nights;

        if (std::cin.fail() || nights <= 0) {
            std::cin.clear();
            std::cin.ignore(200, '\n');
            std::cout << "Invalid nights input :(. Try again!\n" << std::endl;
            continue;
        }

        r->setNights(nights);
        r->calculateTotalPrice(rooms, roomCount);
        std::cout << "Reservation updated successfully :)\n" << std::endl;
        logAction(currentUser->getUsername(), "Updated reservation");
        break;
    }
}


void deleteReservation(Reservation *reservations[], int &reservationCount, User *currentUser) {
    while (true) {
        int id;
        std::cout << "Enter reservation ID to delete: ";
        std::cin >> id;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(200, '\n');
            std::cout << "Invalid input :(. Try again!\n" << std::endl;
            continue;
        }

        int index = -1;
        for (int i = 0; i < reservationCount; i++) {
            if (reservations[i]->getID() == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            std::cout << "Reservation not found :(. Try again!\n" << std::endl;
            continue;
        }

        reservations[index]->getRoom()->setStatus(AVAILABLE);
        delete reservations[index];

        for (int i = index; i < reservationCount - 1; i++) {
            reservations[i] = reservations[i + 1];
        }

        reservationCount--;
        std::cout << "Reservation deleted successfully :))" << std::endl;
        logAction(currentUser->getUsername(), "Deleted reservation with ID:", id);
        break;
    }
}


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

void registerNewGuest(Guest *guests[], int &guestCount, User *currentUser) {
    if (guestCount >= MAX_GUESTS) {
        std::cout << "No space for more guests :(" << std::endl;
        return;
    }

    char temp[BUFFER_SIZE];
    char *name = nullptr, *phone = nullptr, *email = nullptr;

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

    //редактирано
    int newID = guestCount + 1;
    guests[guestCount++] = new Guest(newID, name, phone, email, REGULAR);


    std::cout << "Guest registered successfully :)))" << std::endl;
    logAction(currentUser->getUsername(), "Registered new guest");
    delete[] name;
    delete[] phone;
    delete[] email;
}


void createReservation(Room *rooms[], Guest *guests[], Reservation *reservations[],
                       int roomCount, int guestCount, int &reservationCount, User *currentUser) {
    if (reservationCount >= MAX_RESERVATIONS) {
        std::cout << "No space for more reservations :(" << std::endl;
        return;
    }

    while (true) {
        std::cout << "Guests:" << std::endl;
        for (int i = 0; i < guestCount; i++) {
            std::cout << "ID: " << guests[i]->getID() << " -> " << guests[i]->getName() << std::endl;
        }

        int guestID;
        if (!safeInputInt("Enter guest ID: ", guestID)) {
            std::cout << "Try again!\n" << std::endl;
            continue;
        }

        Guest *selectedGuest = nullptr;
        for (int i = 0; i < guestCount; i++) {
            if (guests[i]->getID() == guestID) {
                selectedGuest = guests[i];
                break;
            }
        }
        if (!selectedGuest) {
            std::cout << "Invalid guest ID :( Try again!\n" << std::endl;
            continue;
        }

        std::cout << "Available rooms:" << std::endl;
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i]->getStatus() == AVAILABLE) {
                std::cout << "Room number: " << rooms[i]->getRoomNum() << std::endl;
            }
        }

        int roomNum;
        if (!safeInputInt("Enter room number: ", roomNum)) {
            std::cout << "Try again!\n" << std::endl;
            continue;
        }

        Room *selectedRoom = nullptr;
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i]->getRoomNum() == roomNum && rooms[i]->getStatus() == AVAILABLE) {
                selectedRoom = rooms[i];
                break;
            }
        }
        if (!selectedRoom) {
            std::cout << "Invalid room number or room is not available :( Try again!\n" << std::endl;
            continue;
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
                std::cout << "Invalid date: " << e.what() << "\nTry again!\n" << std::endl;
            }
        }

        int nights;
        if (!safeInputInt("Enter number of nights: ", nights)) {
            std::cout << "Try again!\n" << std::endl;
            continue;
        }

        if (nights <= 0) {
            std::cout << "Number of nights must be positive :( Try again!\n" << std::endl;
            continue;
        }

        int newIdRes = reservationCount + 1;
        reservations[reservationCount] = new Reservation(
    newIdRes, selectedGuest, selectedRoom, date, nights);
        reservations[reservationCount]->calculateTotalPrice(rooms, roomCount);
        reservationCount++;
        selectedRoom->setStatus(RESERVED);

        std::cout << "Reservation created successfully :)" << std::endl;
        logAction(currentUser->getUsername(), "Created reservation for GuestID:",
                  selectedGuest->getID(), selectedRoom->getRoomNum());
        break;
    }
}


void searchGuestByName(Guest *guests[], int guestCount) {
    std::cin.ignore();

    while (true) {
        char query[BUFFER_SIZE];
        std::cout << "Enter exact name to search: ";
        std::cin.getline(query, BUFFER_SIZE);

        if (strlen(query) == 0) {
            std::cout << "Search term cannot be empty! Try again.\n" << std::endl;
            continue;
        }

        bool found = false;
        for (int i = 0; i < guestCount; i++) {
            if (strcmp(guests[i]->getName(), query) == 0) {
                guests[i]->print();
                std::cout << "-------------------" << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "No guests found with that exact name :( Try again.\n" << std::endl;
            continue;
        }

        break;
    }
}



void searchReservationByDate(Reservation *reservations[], int count) {
    std::cin.ignore();

    while (true) {
        char queryDate[BUFFER_SIZE];
        std::cout << "Enter date (DD.MM.YYYY): ";
        std::cin.getline(queryDate, BUFFER_SIZE);

        try {
            Reservation::dateValidation(queryDate);
        } catch (const std::invalid_argument &e) {
            std::cout << "Invalid date: " << e.what() << "\nTry again!\n" << std::endl;
            continue;
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
            std::cout << "No reservations found for this date :( Try again.\n" << std::endl;
            continue;
        }

        break;
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

void updateGuestStatuses(Guest *guests[], int guestCount, Reservation *reservations[], int reservationCount) {
    for (int i = 0; i < guestCount; i++) {
        int resCount = 0;
        int guestID = guests[i]->getID();

        for (int j = 0; j < reservationCount; j++) {
            if (reservations[j]->getGuest()->getID() == guestID) {
                resCount++;
            }
        }

        if (resCount <= 2) {
            guests[i]->setStatus(REGULAR);
        } else if (resCount <= 5) {
            guests[i]->setStatus(GOLD);
        } else {
            guests[i]->setStatus(PLATINUM);
        }
    }
}

void registerUser(User *users[], int &userCount, User *currentUser) {
    if (userCount >= MAX_USERS) {
        std::cout << "Max number of users reached." << std::endl;
        return;
    }

    while (true) {
        char uname[BUFFER_SIZE], pass[BUFFER_SIZE];
        int roleInput;

        std::cin.ignore();

        std::cout << "Enter new username: ";
        std::cin.getline(uname, BUFFER_SIZE);
        if (strlen(uname) < 1) {
            std::cout << "Username must be at least 1 character. Try again!\n" << std::endl;
            continue;
        }

        std::cout << "Enter password: ";
        std::cin.getline(pass, BUFFER_SIZE);
        if (strlen(pass) < 1) {
            std::cout << "Password must be at least 1 character. Try again!\n" << std::endl;
            continue;
        }

        std::cout << "Select role (0 - MANAGER, 1 - RECEPTIONIST, 2 - ACCOUNTANT): ";
        std::cin >> roleInput;
        if (std::cin.fail() || roleInput < 0 || roleInput > 2) {
            std::cin.clear();
            std::cin.ignore(BUFFER_SIZE, '\n');
            std::cout << "Invalid role selected :(. Try again!\n" << std::endl;
            continue;
        }

        try {
            bool exists = false;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(users[i]->getUsername(), uname) == 0) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                std::cout << "Username already taken. Try another.\n" << std::endl;
                return;
            }
            users[userCount++] = new User(uname, pass, static_cast<Role>(roleInput));
            std::cout << "User created successfully!" << std::endl;
            logAction(currentUser->getUsername(), "Registered new user");
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << "Error: " << e.what() << "\nTry again!\n" << std::endl;
            continue;
        }
    }
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
            std::cout << "9. Add new room" << std::endl;
            std::cout << "10. Edit reservation" << std::endl;
            std::cout << "11. Delete reservation" << std::endl;
            std::cout << "12. Create new user" << std::endl;
            std::cout << "13. Show revenue by day/month/year\n";
            std::cout << "14. Revenue and occupancy by room type" << std::endl;
            std::cout << "15. Exit" << std::endl;
            break;
        case RECEPTIONIST:
            std::cout << "1. Show all rooms" << std::endl;
            std::cout << "2. Show all guests" << std::endl;
            std::cout << "3. Show all reservations" << std::endl;
            std::cout << "4. Register new guest" << std::endl;
            std::cout << "5. Create new reservation" << std::endl;
            std::cout << "6. Show only available rooms" << std::endl;
            std::cout << "7. Search guest by name" << std::endl;
            std::cout << "8. Edit reservation" << std::endl;
            std::cout << "9. Delete reservation" << std::endl;
            std::cout << "10. Exit" << std::endl;
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
    std::ifstream roomIn("rooms.txt");
    while (true) {
        Room *r = Room::loadFromFile(roomIn);
        if (!r) break;
        rooms[roomCount++] = r;
    }
    roomIn.close();


    Guest *guests[MAX_GUESTS];
    int guestCount = 0;
    std::ifstream guestIn("guests.txt");
    while (true) {
        Guest *g = Guest::loadFromFile(guestIn);
        if (!g) break;
        guests[guestCount++] = g;
    }
    guestIn.close();


    Reservation *reservations[MAX_RESERVATIONS];
    int reservationCount = 0;
    std::ifstream resIn("reservations.txt");
    while (resIn && reservationCount < MAX_RESERVATIONS) {
        Reservation *res = Reservation::loadFromFile(resIn, guests, guestCount, rooms, roomCount);
        if (res) reservations[reservationCount++] = res;
    }
    resIn.close();
    User *users[MAX_USERS];
    int userCount = 0;
    std::ifstream userIn("users.txt");
    while (true) {
        User *u = User::loadFromFile(userIn);
        if (!u) break;
        users[userCount++] = u;
    }

    userIn.close();

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
                    case 4: registerNewGuest(guests, guestCount, currentUser);
                        break;
                    case 5: createReservation(rooms, guests, reservations, roomCount, guestCount, reservationCount,
                                              currentUser);
                        updateGuestStatuses(guests, guestCount, reservations, reservationCount);
                        break;
                    case 6: showAvailableRooms(rooms, roomCount);
                        break;
                    case 7: searchGuestByName(guests, guestCount);
                        break;
                    case 8: searchReservationByDate(reservations, reservationCount);
                        break;
                    case 9: addRoom(rooms, roomCount, currentUser);
                        break;
                    case 10: editReservation(reservations, reservationCount, rooms, roomCount, currentUser);
                        break;
                    case 11: deleteReservation(reservations, reservationCount, currentUser);
                        break;
                    case 12: registerUser(users, userCount, currentUser);
                        break;
                    case 13:
                        generateRevenueReportByDate(reservations, reservationCount);
                        break;
                    case 14:
                        generateRevenueAndOccupancyByRoomType(reservations, reservationCount);
                        break;
                    case 15: std::cout << "Bye bye :)";
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
                    case 4: registerNewGuest(guests, guestCount, currentUser);
                        break;
                    case 5: createReservation(rooms, guests, reservations, roomCount, guestCount, reservationCount,
                                              currentUser);
                        updateGuestStatuses(guests, guestCount, reservations, reservationCount);
                        break;
                    case 6: showAvailableRooms(rooms, roomCount);
                        break;
                    case 7: searchGuestByName(guests, guestCount);
                        break;
                    case 8: editReservation(reservations, reservationCount, rooms, roomCount, currentUser);
                        break;
                    case 9: deleteReservation(reservations, reservationCount, currentUser);
                        break;
                    case 10: std::cout << "Bye bye :)";
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
    } while (!((currentUser->getRole() == MANAGER && choice == 15) ||
               (currentUser->getRole() == RECEPTIONIST && choice == 10) ||
               (currentUser->getRole() == ACCOUNTANT && choice == 3)));

    std::ofstream guestOut("guests.txt");
    if(!guestOut.is_open()) return -1;
    for (int i = 0; i < guestCount; i++) {
        guests[i]->saveToFile(guestOut);
    }
    guestOut.close();
    std::ofstream roomOut("rooms.txt");
    if(!roomOut.is_open()) return -1;
    for (int i = 0; i < roomCount; i++) {
        rooms[i]->saveToFile(roomOut);
    }
    roomOut.close();
    std::ofstream resOut("reservations.txt");
    if(!resOut.is_open()) return -1;
    for (int i = 0; i < reservationCount; i++) {
        reservations[i]->saveToFile(resOut);
    }
    resOut.close();

    std::ofstream userOut("users.txt");
    if(!userOut.is_open()) return -1;
    for (int i = 0; i < userCount; i++) {
        users[i]->saveToFile(userOut);
    }
    userOut.close();

    for (int i = 0; i < roomCount; i++) delete rooms[i];
    for (int i = 0; i < guestCount; i++) delete guests[i];
    for (int i = 0; i < reservationCount; i++) delete reservations[i];
    for (int i = 0; i < userCount; i++) delete users[i];

    return 0;
}
