#pragma once
#include "HashTable.h"
#include "Member.h"
#include <iostream>
#include <string>

inline void checkLoanEligibility(HashTable& ht, const std::string& acc) {
    Member* p = ht.search(acc);
    if (!p) {
        std::cout << "Member not found.\n";
        return;
    }
    // Rule: Active status, savings >= 500,000, no outstanding loan.
    bool eligible = (p->status == "Active" && p->savingsBalance >= 500000 && p->loanBalance == 0);
    p->display();
    if (eligible) {
        std::cout << "ELIGIBLE for a loan up to: " << formatMoney(p->savingsBalance * 3) << "\n";
    } else {
        std::cout << "NOT ELIGIBLE. Requires: Active status, savings >= 500,000, no outstanding loan.\n";
    }
}