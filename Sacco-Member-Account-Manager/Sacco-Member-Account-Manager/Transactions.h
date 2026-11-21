#pragma once
#include "AVLTree.h"
#include "HashTable.h"
#include "Member.h"
#include <iostream>
#include <string>

inline bool deposit(HashTable& ht, AVLTree& avl, const std::string& acc, double amount) {
    if (amount <= 0) {
        std::cout << "Amount must be greater than 0.\n";
        return false;
    }
    Member* p = ht.search(acc);
    if (!p) {
        std::cout << "Member not found.\n";
        return false;
    }
    Member old = *p;
    p->savingsBalance += amount;
    avl.remove(old);
    avl.insert(*p);
    std::cout << "Deposit successful. New Balance: " << formatMoney(p->savingsBalance) << "\n";
    return true;
}

inline bool withdraw(HashTable& ht, AVLTree& avl, const std::string& acc, double amount) {
    if (amount <= 0) {
        std::cout << "Amount must be greater than 0.\n";
        return false;
    }
    Member* p = ht.search(acc);
    if (!p) {
        std::cout << "Member not found.\n";
        return false;
    }
    if (amount > p->savingsBalance) {
        std::cout << "Insufficient funds! Balance: " << formatMoney(p->savingsBalance) << "\n";
        return false;
    }
    Member old = *p;
    p->savingsBalance -= amount;
    avl.remove(old);
    avl.insert(*p);
    std::cout << "Withdrawal successful. New Balance: " << formatMoney(p->savingsBalance) << "\n";
    return true;
}