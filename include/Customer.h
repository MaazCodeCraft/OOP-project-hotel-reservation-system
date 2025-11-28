#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
using namespace std;

class Customer {
private:
    static int lastID;
    int customerID;
    string customerName;
    string customerAddress;
    string customerPhone;
    string customerEmail;

    bool isValidEmail(const string &email) const;
    bool isValidPhone(const string &phone) const;

public:
    Customer();
    Customer(int last_ID, int customer_ID, const string &name, const string &address,
             const string &phone, const string &email);

    static void setLastID(int last_ID);
    static int getLastID();

    void setCustomerID(int customer_ID);
    int getCustomerID() const;

    void setCustomerName(const string &name);
    void setCustomerName();
    string getCustomerName() const;

    void setCustomerAddress(const string &address);
    void setCustomerAddress();
    string getCustomerAddress() const;

    void setCustomerPhone(const string &phone);
    void setCustomerPhone();
    string getCustomerPhone() const;

    void setCustomerEmail(const string &email);
    void setCustomerEmail();
    string getCustomerEmail() const;

    void getDetails() const;
    void getDetailsFlat() const;
};

Customer *checkCustomer(vector<Customer> &customers, int id);
void viewAllCustomers(const vector<Customer> &customers);

#endif