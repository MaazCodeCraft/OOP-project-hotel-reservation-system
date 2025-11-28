#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>

#include "Customer.h"
#include "Hotel.h"
using namespace std;

class Admin {
private:
    string username;
    string password;
    bool superAdmin;

    void setUsernameWithPrompt();
    void setPasswordWithConfirmation();
    string getPasswordInput(const string &prompt);

public:
    Admin(bool super = false);
    Admin(const string &user, const string &pass, bool super = false);

    void setUsername(const string &user);
    string getUsername() const;

    void setPassword(const string &pass);
    string getPassword() const;

    void setSuperAdmin(bool super);
    bool isSuper() const;
};

bool checkAdmin(vector<Admin> &admins, string username, string password);
bool loginScreen(vector<Admin> &admins);
void menuScreen(vector<Admin> &admins, vector<Customer> &customers, Hotel &hotel);

#endif