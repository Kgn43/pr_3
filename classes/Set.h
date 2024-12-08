#ifndef SET_H
#define SET_H

#include "list.h"
#include "arr.h"
#include <iostream>

#define BUCKETS 10

using std::cout, std::endl, std::ostream, std::to_string;

class Set {
    arr<List<int>> buckets;
    size_t bucketCount;
    size_t pairCount;

    void coliseum();
    size_t hash(const int& value) const;
public:
    Set(): buckets(BUCKETS), bucketCount(BUCKETS), pairCount(0){} //создаёт BUCKETS бакет
    explicit Set(const size_t num): buckets(num), bucketCount(num), pairCount(0){} //создаёт num бакетов

    void insert(const int& value);
    void del(const int& value);
    bool at(const int& value) const;
    int Get() const;
    size_t size() const;
    size_t get_buckets() const;

    friend ostream& operator<<(ostream& os, const Set& set) {
        os << "{";
        bool z = true;
        for (size_t i = 0; i < set.bucketCount; i++){
            if (set.buckets[i].first == nullptr) continue;
            auto node = set.buckets[i].first;
            if (z) {
                z = false;
            }
            else {
                os << ", ";
            }
            while (node != nullptr) {
                os << node->value;
                if (node->next != nullptr ) {
                    os << ", ";
                }
                node = node->next;
            }
        }
        os << "}" << endl;
        return os;
    }

    List<int>& operator[](size_t index) const {
        if (index >= this->bucketCount) {
            throw std::out_of_range("Index out of range");
        }
        return this->buckets[index];
    }

};

#endif //SET_H
