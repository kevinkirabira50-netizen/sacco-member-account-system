#include "AVLTree.h"
#include "HashTable.h"
#include "MemberOps.h"
#include "Transactions.h"

#include <iostream>
#include <string>

namespace {

int failures = 0;

// Unlike assert, CHECK always runs, even when NDEBUG is defined.
#define CHECK(cond)                                                        \
    do {                                                                   \
        if (!(cond)) {                                                     \
            std::cerr << "FAILED (line " << __LINE__ << "): " #cond "\n";  \
            ++failures;                                                    \
        }                                                                  \
    } while (0)

}  // namespace

int main() {
    HashTable ht;
    AVLTree avl;

    Member m1{"SAC-001", "John", "Mukasa", "CM1", "0771", 500000, 0, 50, "2024-01-15", "Active"};
    Member m2{"SAC-002", "Sarah", "Nakato", "CM2", "0772", 800000, 0, 80, "2024-02-10", "Active"};

    // Add
    CHECK(addMember(ht, avl, m1) == true);
    // Duplicate rejected
    CHECK(addMember(ht, avl, m1) == false);
    // Second member
    CHECK(addMember(ht, avl, m2) == true);
    // Search existing and missing
    CHECK(ht.search("SAC-001") != nullptr);
    CHECK(ht.search("SAC-999") == nullptr);
    // Negative deposit rejected
    CHECK(deposit(ht, avl, "SAC-001", -100) == false);
    // Overdraw rejected
    CHECK(withdraw(ht, avl, "SAC-001", 9999999) == false);
    // Valid deposit updates balance
    CHECK(deposit(ht, avl, "SAC-001", 100000) == true);
    CHECK(ht.search("SAC-001") != nullptr && ht.search("SAC-001")->savingsBalance == 600000);

    // AVL stays balanced after sorted inserts. Balances end in 50,000 so
    // none collide with existing balances.
    for (int i = 3; i <= 10; i++) {
        std::string num = std::to_string(i);
        num = std::string(3 - num.size(), '0') + num;   // SAC-003 .. SAC-010
        Member m{"SAC-" + num, "Test", "User" + std::to_string(i), "CM", "077",
                 static_cast<double>(i) * 100000 + 50000, 0, 10, "2024-01-01", "Active"};
        CHECK(addMember(ht, avl, m) == true);
    }
    // 10 nodes: an AVL tree has height at most 4 (a plain BST would reach 10).
    CHECK(avl.getHeight() <= 4);
    CHECK(avl.inOrder().size() == ht.size());

    // Delete
    CHECK(deleteMember(ht, avl, "SAC-001") == true);
    CHECK(ht.search("SAC-001") == nullptr);
    CHECK(avl.inOrder().size() == ht.size());

    if (failures == 0) {
        std::cout << "ALL TESTS PASSED!\n";
        return 0;
    }
    std::cout << failures << " TEST(S) FAILED\n";
    return 1;
}