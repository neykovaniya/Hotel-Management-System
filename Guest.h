//
// Created by Niya Neykova on 24.05.25.
//
#pragma once
enum guestStatus {
    REGULAR,
    GOLD,
    PLATINUM
};
class Guest {
private:
    int id;
    char* name=nullptr;
    int* phone = nullptr;
    char* email = nullptr;
    guestStatus status;
    void free();
    void copyFrom(const Guest& other);
public:
    Guest(int _id,const char* _name, const int* _phone, const char* _email, guestStatus _status);
    Guest(const Guest& other);
    Guest& operator=(const Guest& other);
    ~Guest();
    void setName(const char* _name);
    void setPhone(const int* _phone);
    void setEmail(const char* _email);
    void setStatus(guestStatus _status);
    [[nodiscard]] int getID() const;
    [[nodiscard]] const char* getName() const;
    [[nodiscard]] const int* getPhone() const;
    [[nodiscard]] const char* getEmail() const;
    [[nodiscard]] guestStatus getStatus() const;
    void print() const;
};