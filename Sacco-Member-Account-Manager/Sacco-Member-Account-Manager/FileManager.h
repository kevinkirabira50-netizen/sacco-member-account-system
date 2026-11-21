#pragma once
#include "Member.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Splits on every delimiter, keeping empty fields (including a trailing one).
inline std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string current;
    for (char c : s) {
        if (c == delim) {
            out.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    out.push_back(current);
    return out;
}

inline std::vector<Member> loadFromFile(const std::string& filename) {
    std::vector<Member> members;
    std::ifstream in(filename);
    if (!in) {
        std::cout << "No existing file. Starting with an empty SACCO.\n";
        return members;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();  // Windows line endings
        if (line.empty()) continue;

        auto p = split(line, '|');
        if (p.size() != 10) {
            std::cout << "Skipping corrupt line: " << line << "\n";
            continue;
        }
        try {
            Member m;
            m.accountNo = p[0];
            m.firstName = p[1];
            m.lastName = p[2];
            m.nationalID = p[3];
            m.phone = p[4];
            m.savingsBalance = std::stod(p[5]);
            m.loanBalance = std::stod(p[6]);
            m.shares = std::stoi(p[7]);
            m.dateJoined = p[8];
            m.status = p[9];
            members.push_back(m);
        } catch (const std::exception&) {
            std::cout << "Skipping line with invalid number: " << line << "\n";
        }
    }
    return members;
}

inline bool saveToFile(const std::string& filename, const std::vector<Member>& members) {
    std::ofstream out(filename);
    if (!out) return false;
    out << std::fixed << std::setprecision(2);           // keep money exact on disk
    for (const Member& m : members) {
        out << m.accountNo << '|' << m.firstName << '|' << m.lastName << '|'
            << m.nationalID << '|' << m.phone << '|' << m.savingsBalance << '|'
            << m.loanBalance << '|' << m.shares << '|' << m.dateJoined << '|'
            << m.status << '\n';
    }
    return static_cast<bool>(out);
}