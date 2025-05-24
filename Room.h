//
// Created by Niya Neykova on 24.05.25.
//
#pragma once
enum roomType {
    SINGLE,
    DOUBLE,
    DELUXE,
    CONFERENCE_HALL,
    APARTMENT
};
enum roomStatus {
    AVAILABLE,
    RESERVED,
    UNDER_MAINTENANCE
};
class Room {
private:
    int roomNum;
    roomType type;
    roomStatus status;
    double price;
public:
    Room(int _roomNum,roomType _type, roomStatus _status, double _price);
    void setStatus(roomStatus _status);
    void setPrice(double _price);
    [[nodiscard]] int getRoomNum() const;
    [[nodiscard]] roomType getType() const;
    [[nodiscard]] roomStatus getStatus() const;
    [[nodiscard]] double getPricePerNight() const;
    void print() const;
};