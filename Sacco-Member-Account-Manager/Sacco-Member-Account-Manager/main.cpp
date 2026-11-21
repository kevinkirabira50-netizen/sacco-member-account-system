#include "AVLTree.h"
#include "FileManager.h"
#include "HashTable.h"
#include "MemberOps.h"
#include "Member.h"
#include "Report.h"
#include "SaccoOps.h"
#include "Transactions.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

namespace {

const std::string DATA_FILE = "members.txt";

template <typename T>
T readNumber(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        T value;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        if (std::cin.eof()) {
            std::cout << "\nInput closed. Exiting.\n";
            std::exit(0);
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Enter a number.\n";
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

void addNewMember(HashTable& ht, AVLTree& avl) {
    Member m;
    m.accountNo = readLine("Account No (e.g. SAC-007): ");
    m.firstName = readLine("First Name: ");
    m.lastName = readLine("Last Name: ");
    m.nationalID = readLine("National ID: ");
    m.phone = readLine("Phone: ");
    m.savingsBalance = readNumber<double>("Savings Balance: ");
    m.loanBalance = readNumber<double>("Loan Balance: ");
    m.shares = readNumber<int>("Shares: ");
    m.dateJoined = readLine("Date Joined (YYYY-MM-DD): ");
    m.status = readLine("Status (Active/Inactive): ");
    addMember(ht, avl, m);
}

void printMenu() {
    std::cout << "\n===== SACCO MEMBER ACCOUNT MANAGER =====\n"
              << "1. Add Member\n"
              << "2. Search Member\n"
              << "3. Update Member\n"
              << "4. Delete Member\n"
              << "5. Deposit\n"
              << "6. Withdraw\n"
              << "7. Loan Eligibility\n"
              << "8. Report by Balance\n"
              << "9. Report by Name\n"
              << "0. Save & Exit\n";
}

}  // namespace

int main() {
    HashTable ht;
    AVLTree avl;

    for (const Member& m : loadFromFile(DATA_FILE)) {
        ht.insert(m);
        avl.insert(m);
    }
    std::cout << "Loaded " << ht.size() << " members.\n";

    while (true) {
        printMenu();
        int choice = readNumber<int>("Choice: ");

        switch (choice) {
            case 0:
                if (saveToFile(DATA_FILE, ht.getAll()))
                    std::cout << "Saved. Goodbye!\n";
                else
                    std::cerr << "ERROR: could not write " << DATA_FILE << "\n";
                return 0;
            case 1:
                addNewMember(ht, avl);
                break;
            case 2: {
                Member* p = ht.search(readLine("Account No to search: "));
                if (p) p->display();
                else std::cout << "Not found.\n";
                break;
            }
            case 3: {
                std::string acc = readLine("Account No to update: ");
                std::string phone = readLine("New Phone: ");
                std::string status = readLine("New Status: ");
                updateMember(ht, avl, acc, phone, status);
                break;
            }
            case 4:
                deleteMember(ht, avl, readLine("Account No to delete: "));
                break;
            case 5: {
                std::string acc = readLine("Account No: ");
                double amt = readNumber<double>("Deposit amount: ");
                deposit(ht, avl, acc, amt);
                break;
            }
            case 6: {
                std::string acc = readLine("Account No: ");
                double amt = readNumber<double>("Withdraw amount: ");
                withdraw(ht, avl, acc, amt);
                break;
            }
            case 7:
                checkLoanEligibility(ht, readLine("Account No: "));
                break;
            case 8:
                printByBalance(avl);
                break;
            case 9:
                printByName(ht);
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}