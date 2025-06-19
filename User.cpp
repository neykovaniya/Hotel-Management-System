#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include "User.h"

const int MAX_SIZE = 1000;

void User::copyFrom(const User &other) {
    role = other.role;
    username = new char[strlen(other.username) + 1];
    strcpy(username, other.username);
    password = new char[strlen(other.password) + 1];
    strcpy(password, other.password);
}

void User::free() {
    delete[] username;
    delete[] password;
    username = nullptr;
    password = nullptr;
}

User::User(const char *_username, const char *_password, Role _role) : role(_role) {
    usernameValidation(_username);
    passwordValidation(_password);
    username = new char[strlen(_username) + 1];
    strcpy(username, _username);
    password = new char[strlen(_password) + 1];
    strcpy(password, _password);
}

User::User(const User &other) {
    copyFrom(other);
}

User &User::operator=(const User &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

User::~User() {
    free();
}

const char *User::getUsername() const {
    return username;
}

const char *User::getPassword() const {
    return password;
}

Role User::getRole() const {
    return role;
}

void User::setUsername(const char *_username) {
    usernameValidation(_username);
    delete[] username;
    username = new char[strlen(_username) + 1];
    strcpy(username, _username);
}

void User::setPassword(const char *_password) {
    passwordValidation(_password);
    delete[] password;
    password = new char[strlen(_password) + 1];
    strcpy(password, _password);
}

void User::setRole(Role _role) {
    role = _role;
}

void User::print() const {
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Role: ";
    switch (role) {
        case MANAGER:
            std::cout << "Manager";
            break;
        case RECEPTIONIST:
            std::cout << "Receptionist";
            break;
        case ACCOUNTANT:
            std::cout << "Accountant";
            break;
    }
    std::cout << std::endl;
}

void User::usernameValidation(const char *_username) const {
    if (!_username || strlen(_username) < 1) {
        throw std::invalid_argument("Username must be at least 1 character :(");
    }
}

void User::passwordValidation(const char *_password) const {
    if (!_password || strlen(_password) < 1) {
        throw std::invalid_argument("Password must be at least 1 character :(");
    }
}

void User::saveToFile(std::ofstream &out) const {
    out << username << '\n'
            << password << '\n'
            << static_cast<int>(role) << '\n';
}

//редактирано
User *User::loadFromFile(std::ifstream &in) {
    char uname[100], pass[100];
    int roleInt;

    if (!in.getline(uname, MAX_SIZE)) return nullptr;
    if (!in.getline(pass, MAX_SIZE)) return nullptr;
    if (!(in >> roleInt)) return nullptr;
    in.ignore();

    return new User(uname, pass, static_cast<Role>(roleInt));
}
