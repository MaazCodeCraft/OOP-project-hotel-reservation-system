#include "../include/Customer.h"

#include <iostream>
#include <regex>

#include "../include/Colors.h"

using namespace std;

int Customer::lastID = 0;

Customer::Customer() {
    customerID = ++lastID;
    cin.ignore();
    cout << "Customer ID: " << customerID << endl;
    setCustomerName();
    setCustomerAddress();
    setCustomerPhone();
    setCustomerEmail();
}

Customer::Customer(int last_ID, int customer_ID, const string& name, const string& address,
                   const string& phone, const string& email) {
    setLastID(last_ID);
    setCustomerID(customer_ID);
    setCustomerName(name);
    setCustomerAddress(address);
    setCustomerPhone(phone);
    setCustomerEmail(email);
}

void Customer::setLastID(int last_ID) { lastID = last_ID; }

int Customer::getLastID() { return lastID; }

void Customer::setCustomerID(int customer_ID) { customerID = customer_ID; }

int Customer::getCustomerID() const { return customerID; }

void Customer::setCustomerName(const string& name) {
    if (!name.empty()) {
        customerName = name;
    } else {
        throw invalid_argument("Customer name cannot be empty.");
    }
}

void Customer::setCustomerName() {
    while (true) {
        cout << "Customer Name: ";
        getline(cin, customerName);
        if (!customerName.empty()) {
            break;
        } else {
            cerr << '\a';
            cout << "Customer name cannot be empty. Please enter the customer name." << endl;
        }
    }
}

string Customer::getCustomerName() const { return customerName; }

void Customer::setCustomerAddress(const string& address) {
    if (!address.empty()) {
        customerAddress = address;
    } else {
        throw invalid_argument("Customer address cannot be empty.");
    }
}

void Customer::setCustomerAddress() {
    while (true) {
        cout << "Customer Address: ";
        getline(cin, customerAddress);
        if (!customerAddress.empty()) {
            break;
        } else {
            cerr << '\a';
            cout << "Customer address cannot be empty. Please enter the customer address." << endl;
        }
    }
}

string Customer::getCustomerAddress() const { return customerAddress; }

void Customer::setCustomerPhone(const string& phone) {
    if (isValidPhone(phone)) {
        customerPhone = phone;
    } else {
        cerr << '\a';
        throw invalid_argument("Phone number must be exactly 11 digits and contain only numbers.");
    }
}

void Customer::setCustomerPhone() {
    while (true) {
        cout << "Customer Phone: ";
        getline(cin, customerPhone);
        if (isValidPhone(customerPhone)) {
            break;
        } else {
            cerr << '\a';
            cout << RED
                 << "Invalid phone number. It must be exactly 11 digits and contain only numbers. "
                    "Please re-enter the phone number."
                 << RESET << endl;
        }
    }
}

string Customer::getCustomerPhone() const { return customerPhone; }

void Customer::setCustomerEmail(const string& email) {
    if (isValidEmail(email)) {
        customerEmail = email;
    } else {
        cerr << '\a';
        throw invalid_argument("Invalid email format");
    }
}

void Customer::setCustomerEmail() {
    while (true) {
        cout << "Customer Email: ";
        getline(cin, customerEmail);
        if (isValidEmail(customerEmail)) {
            break;
        } else {
            cerr << '\a';
            cout << YELLOW << "Invalid email format. Please re-enter the email." << RESET << endl;
        }
    }
}

string Customer::getCustomerEmail() const { return customerEmail; }

void Customer::getDetails() const {
    cout << "Customer ID: " << customerID << endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Customer Address: " << customerAddress << endl;
    cout << "Customer Phone: " << customerPhone << endl;
    cout << "Customer Email: " << customerEmail << endl;
}

void Customer::getDetailsFlat() const {
    cout << CYAN << "\n[" << (customerID < 10 ? "00" : (customerID < 100 ? "0" : "")) << customerID
         << "] " << RESET;
    cout << BOLD << "NAME\t: " << RESET << customerName << "\n      " << BOLD
         << "ADDRESS\t: " << RESET << customerAddress;
    cout << "\n      " << BOLD << "PHONE\t: " << RESET << customerPhone << "\n      " << BOLD
         << "EMAIL\t: " << RESET << customerEmail;
    cout << endl;
}

bool Customer::isValidEmail(const string& email) const {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
}

bool Customer::isValidPhone(const string& phone) const {
    const regex pattern("^\\d{11}$");
    return regex_match(phone, pattern);
}

Customer* checkCustomer(vector<Customer>& customers, int id) {
    for (size_t i = 0; i < customers.size(); i++) {
        if (customers[i].getCustomerID() == id) {
            customers[i].getDetails();
            return &customers[i];
        }
    }
    return nullptr;
}

void viewAllCustomers(const vector<Customer>& customers) {
    if (customers.empty()) {
        cout << "\nNo Registered Customers Yet!";
    } else {
        for (const auto& customer : customers) {
            customer.getDetailsFlat();
        }
    }
}