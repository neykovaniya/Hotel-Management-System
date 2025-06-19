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
    static int nextRoomNum;

public:
    Room(int _roomNum, roomType _type, roomStatus _status, double _price);

    Room(roomType _type, roomStatus _status, double _price);

    void setStatus(roomStatus _status);

    void setPrice(double _price);

    [[nodiscard]] int getRoomNum() const;

    [[nodiscard]] roomType getType() const;

    [[nodiscard]] roomStatus getStatus() const;

    [[nodiscard]] double getPricePerNight() const;

    void print() const;

    void saveToFile(std::ofstream &out) const;

    static Room *loadFromFile(std::ifstream &in);

    double getDynamicPrice(const char *dateStr, double occupancyRate) const;

    static int getNextRoomNum();

    [[nodiscard]] Room* clone() const;
};
