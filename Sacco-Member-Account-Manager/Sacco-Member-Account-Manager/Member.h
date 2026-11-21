#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Formats an amount with exactly 2 decimal places, e.g. 1234567 -> "1234567.00".
inline std::string formatMoney(double value) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2) << value;
    return os.str();
}

struct Member {
    std::string accountNo;
    std::string firstName;
    std::string lastName;
    std::string nationalID;
    std::string phone;
    double savingsBalance = 0.0;
    double loanBalance = 0.0;
    int shares = 0;
    std::string dateJoined;
    std::string status = "Active";  // Active / Inactive

    std::string fullName() const { return firstName + " " + lastName; }

    void display() const {
        std::cout << "----------------------------------------\n"
                  << "Account No: " << accountNo << " | Name: " << fullName() << "\n"
                  << "National ID: " << nationalID << " | Phone: " << phone << "\n"
                  << "Savings: " << formatMoney(savingsBalance)
                  << " | Loan: " << formatMoney(loanBalance)
                  << " | Shares: " << shares << "\n"
                  << "Joined: " << dateJoined << " | Status: " << status << "\n";
    }
};