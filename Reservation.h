#pragma once
#include "Room.h"
#include "Guest.h"

class Reservation {
private:
    int id;
    Guest *guest;
    Room *room;
    int nights;
    char *checkInDate;
    double totalPrice;

    void free();

    void copyFrom(const Reservation &other);

public:
    Reservation(int _id, Guest *_guest, Room *_room, const char *_checkInDate, int _nights);

    Reservation(const Reservation &other);

    Reservation &operator=(const Reservation &other);

    ~Reservation();

    void setDate(const char *_date);

    void setNights(int _nights);

    void calculateTotalPrice();

    void calculateTotalPrice(Room *rooms[], int roomCount);

    [[nodiscard]] int getID() const;

    [[nodiscard]] Guest *getGuest() const;

    [[nodiscard]] Room *getRoom() const;

    [[nodiscard]] const char *getCheckInDate() const;

    [[nodiscard]] int getNights() const;

    [[nodiscard]] double getTotalPrice() const;

    void print() const;

    static void dateValidation(const char *_date);

    void saveToFile(std::ofstream &out) const;

    static Reservation *loadFromFile(std::ifstream &in, Guest *guests[], int guestCount, Room *rooms[], int roomCount);
};
