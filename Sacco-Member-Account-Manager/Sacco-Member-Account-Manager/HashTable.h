#pragma once
#include "Member.h"
#include <cstddef>
#include <list>
#include <string>
#include <vector>

class HashTable {
public:
    explicit HashTable(std::size_t capacity = 101)
        : buckets(capacity > 0 ? capacity : 1) {}

    // Returns false if the account number already exists.
    bool insert(const Member& m) {
        if (search(m.accountNo) != nullptr) return false;
        buckets[indexFor(m.accountNo)].push_back(m);
        ++count;
        return true;
    }

    // Returns a pointer into the table, or nullptr if not found.
    Member* search(const std::string& acc) {
        for (Member& m : buckets[indexFor(acc)])
            if (m.accountNo == acc) return &m;
        return nullptr;
    }

    bool remove(const std::string& acc) {
        auto& bucket = buckets[indexFor(acc)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->accountNo == acc) {
                bucket.erase(it);
                --count;
                return true;
            }
        }
        return false;
    }

    std::vector<Member> getAll() const {
        std::vector<Member> all;
        all.reserve(count);
        for (const auto& bucket : buckets)
            for (const Member& m : bucket) all.push_back(m);
        return all;
    }

    std::size_t size() const { return count; }

    void clear() {
        for (auto& bucket : buckets) bucket.clear();
        count = 0;
    }

private:
    std::vector<std::list<Member>> buckets;
    std::size_t count = 0;

    std::size_t indexFor(const std::string& key) const {
        unsigned long long h = 0;
        for (unsigned char c : key) h = h * 31 + c;   // polynomial hash
        return static_cast<std::size_t>(h % buckets.size());
    }
};