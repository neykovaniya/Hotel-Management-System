//
// Created by Niya Neykova on 24.05.25.
//
#include <iostream>
#include <cstring>
#include "Guest.h"

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
    nameValidation(_name);
    phoneValidation(_phone);
    emailValidation(_email);
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
    nameValidation(_name);
    delete[] name;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}

void Guest::setPhone(const char *_phone) {
    phoneValidation(_phone);
    delete[]phone;
    phone = new char[strlen(_phone) + 1];
    strcpy(phone, _phone);
}

void Guest::setEmail(const char *_email) {
    emailValidation(_email);
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

void Guest::nameValidation(const char *_name) const {
    if (!_name || strlen(_name) < 1) {
        throw std::invalid_argument("Username must be at least 1 character :(");
    }
}

void Guest::phoneValidation(const char *_phone) const {
    if (!_phone) {
        throw std::invalid_argument("Phone cannot be null :(");
    }
    if (strlen(_phone) != 10) {
        throw std::invalid_argument("Phone must be exactly 10 digits :(");
    }
    for (int i = 0; i < 10; ++i) {
        if (!(_phone[i] >= '0' && _phone[i] <= '9')) {
            throw std::invalid_argument("Phone must contain only digits :(");
        }
    }
}

void Guest::emailValidation(const char *email) const {
    if (!email) {
        throw std::invalid_argument("Email cannot be null :(");
    }
    const char *at = strchr(email, '@');
    if (!at) {
        throw std::invalid_argument("Email must contain '@' :(");
    }
    const char *dot = strchr(at, '.');
    if (!dot) {
        throw std::invalid_argument("Email must contain '.' after '@' :(");
    }
    if (email[0] == '@') {
        throw std::invalid_argument("Email cannot start with '@' :(");
    }
    for (size_t i = 0; i < strlen(email); i++) {
        if (email[i] == ' ') {
            throw std::invalid_argument("Email cannot contain spaces :(");
        }
    }
}
