# SACCO Member Account Manager

A console program for managing SACCO member accounts: adding, searching, updating and deleting members, deposits, withdrawals, loan eligibility checks, and sorted reports.

## Building

Requires a C++17 compiler (g++ or clang++).

    make          # builds ./sacco and ./tests
    make test     # runs the unit tests
    make clean    # removes the built programs

Without make:

    g++ -std=c++17 -Wall -Wextra -pedantic -O2 -o sacco main.cpp
    g++ -std=c++17 -Wall -Wextra -pedantic -O2 -o tests tests.cpp

## Running

    ./sacco

The program reads `members.txt` from the current folder when it starts and writes it back when you choose "0. Save & Exit". Keep a backup of this file.

## Data file format

`members.txt` has one member per line, with exactly 10 fields separated by `|`:

    accountNo|firstName|lastName|nationalID|phone|savings|loan|shares|dateJoined|status

Example:

    SAC-001|John|Mukasa|CM1234567|0771000001|500000.00|0.00|50|2024-01-15|Active

Lines with the wrong number of fields or invalid numbers are skipped with a message when the program starts. They are not deleted from the file until the next save, so check the warnings if members go missing.

## Files

| File | Purpose |
|---|---|
| `main.cpp` | Menu and user input |
| `Member.h` | The `Member` record and money formatting |
| `HashTable.h` | Fast lookup by account number |
| `AVLTree.h` | Self-balancing tree ordered by savings, used for balance reports |
| `FileManager.h` | Loading and saving `members.txt` |
| `MemberOps.h` | Add, delete and update members |
| `Transactions.h` | Deposits and withdrawals |
| `SaccoOps.h` | Loan eligibility check |
| `Report.h` | Reports by balance and by name |
| `tests.cpp` | Unit tests |
| `Makefile` | Build rules |

## Loan eligibility rule

A member is eligible if the status is Active, savings are at least 500,000, and there is no outstanding loan. The maximum loan shown is three times savings.
