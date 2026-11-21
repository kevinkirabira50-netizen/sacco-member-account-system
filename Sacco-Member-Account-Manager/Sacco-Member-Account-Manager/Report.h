#pragma once
#include "AVLTree.h"
#include "HashTable.h"
#include "Member.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

inline void printRow(const Member& m) {
    std::cout << m.accountNo << " | " << m.fullName()
              << " | Savings: " << formatMoney(m.savingsBalance) << "\n";
}

inline void printByBalance(const AVLTree& avl) {
    std::vector<Member> v = avl.inOrder();   // ascending by savings

    std::cout << "\n=== ORDERED REPORT: BY SAVINGS BALANCE (Low to High) ===\n";
    if (v.empty()) {
        std::cout << "No members.\n";
        return;
    }
    for (const Member& m : v) printRow(m);

    std::cout << "\n=== TOP SAVERS (High to Low) ===\n";
    for (auto it = v.rbegin(); it != v.rend(); ++it) printRow(*it);
}

inline void printByName(HashTable& ht) {
    std::vector<Member> v = ht.getAll();

    // Last name, then first name, then account number, so the order is stable.
    std::sort(v.begin(), v.end(), [](const Member& a, const Member& b) {
        return std::tie(a.lastName, a.firstName, a.accountNo)
             < std::tie(b.lastName, b.firstName, b.accountNo);
    });

    std::cout << "\n=== ORDERED REPORT: BY NAME A-Z ===\n";
    if (v.empty()) {
        std::cout << "No members.\n";
        return;
    }
    for (const Member& m : v) printRow(m);
}