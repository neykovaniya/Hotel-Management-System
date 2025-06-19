#pragma once
enum Role {
    MANAGER,
    RECEPTIONIST,
    ACCOUNTANT
};

class User {
private:
    char *username;
    char *password;
    Role role;

    void copyFrom(const User &other);

    void free();

public:
    User(const char *_username, const char *_password, Role _role);

    User(const User &other);

    User &operator=(const User &other);

    ~User();

    [[nodiscard]] const char *getUsername() const;

    [[nodiscard]] const char *getPassword() const;

    [[nodiscard]] Role getRole() const;

    void setUsername(const char *_username);

    void setPassword(const char *_password);

    void setRole(Role _role);

    void print() const;

    void usernameValidation(const char *_username) const;

    void passwordValidation(const char *_password) const;

    void saveToFile(std::ofstream &out) const;

    static User *loadFromFile(std::ifstream &in);
};
