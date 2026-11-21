#pragma once
#include "AVLTree.h"
#include "HashTable.h"
#include "Member.h"
#include <iostream>
#include <string>

inline bool addMember(HashTable& ht, AVLTree& avl, const Member& m) {
    if (m.accountNo.empty()) {
        std::cout << "Account No cannot be empty.\n";
        return false;
    }
    if (!ht.insert(m)) {
        std::cout << "Duplicate Account No! Member not added.\n";
        return false;
    }
    avl.insert(m);
    std::cout << "Member added successfully.\n";
    return true;
}

inline bool deleteMember(HashTable& ht, AVLTree& avl, const std::string& acc) {
    Member* p = ht.search(acc);
    if (!p) {
        std::cout << "Member not found.\n";
        return false;
    }
    Member copy = *p;          // must match what is stored in the tree
    ht.remove(acc);
    avl.remove(copy);
    std::cout << "Member deleted.\n";
    return true;
}

inline bool updateMember(HashTable& ht, AVLTree& avl, const std::string& acc,
                         const std::string& newPhone, const std::string& newStatus) {
    Member* p = ht.search(acc);
    if (!p) {
        std::cout << "Member not found.\n";
        return false;
    }
    Member old = *p;
    p->phone = newPhone;
    p->status = newStatus;
    avl.remove(old);
    avl.insert(*p);
    std::cout << "Member updated.\n";
    return true;
}