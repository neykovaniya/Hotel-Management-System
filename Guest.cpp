//
// Created by Niya Neykova on 24.05.25.
//
#include <iostream>
#include <cstring>
#include "Guest.h"
const int MAX_PHONE_SIZE = 10;

void Guest::free() {
    delete[] name;
    delete[] phone;
    delete[] email;
    name = nullptr;
    phone = nullptr;
    email = nullptr;
}

void Guest::copyFrom(const Guest &other) {
    id = other.id;
    status = other.status;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    phone = new char[strlen(other.phone) + 1];
    strcpy(phone, other.phone);
    email = new char[strlen(other.email) + 1];
    strcpy(email, other.email);
}

Guest::Guest(int _id, const char *_name, const char *_phone, const char *_email,
             guestStatus _status): id(_id), status(_status) {
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
    phone = new char[strlen(_phone) + 1];
    strcpy(phone, _phone);
    email = new char[strlen(_email) + 1];
    strcpy(email, _email);
}

Guest::Guest(const Guest &other) {
    copyFrom(other);
}

Guest &Guest::operator=(const Guest &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Guest::~Guest() {
    free();
}

void Guest::setName(const char *_name) {
    delete[] name;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}

void Guest::setPhone(const char *_phone) {
    delete[]phone;
    phone = new char[strlen(_phone) + 1];
    strcpy(phone, _phone);
}

void Guest::setEmail(const char *_email) {
    delete[] email;
    email = new char[strlen(_email) + 1];
    strcpy(email, _email);
}

void Guest::setStatus(guestStatus _status) {
    status = _status;
}

int Guest::getID() const {
    return id;
}

const char *Guest::getName() const {
    return name;
}

const char *Guest::getPhone() const {
    return phone;
}

const char *Guest::getEmail() const {
    return email;
}

guestStatus Guest::getStatus() const {
    return status;
}

void Guest::print() const {
    std::cout << "Guest " << id << std::endl;
    std::cout << "Name: ";
    if (name) std::cout << name << std::endl;
    std::cout << "Phone: ";
    if (phone) std::cout << phone << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Status: ";
    switch (status) {
        case REGULAR:
            std::cout << "Regular";
            break;
        case GOLD:
            std::cout << "Gold";
            break;
        case PLATINUM:
            std::cout << "Platinum";
            break;
    }
    std::cout << std::endl;
}
