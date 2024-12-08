#ifndef HASHMAP_H
#define HASHMAP_H

#include "list.h"
#include "arr.h"
#include "Pair.h"
#include <iostream>

using std::endl, std::cout, std::string;

class hashMap {
    arr<List<Pair>> buckets;
    size_t bucketCount;
    size_t pairCount;

    void coliseum();
public:
    hashMap(): pairCount(0), bucketCount(2), buckets(2){} //создаёт 4 бакета
    hashMap(size_t num): pairCount(0), bucketCount(num), buckets(num){} //создаёт num бакетов

    void insert(const string& key, const string& value);
    void insert(const Pair& input);
    void del(const string& key);
    size_t hash(const string& key) const;
    Pair Get(const string& key) const;
    Pair Get() const;
    size_t get_size() const;
    size_t get_bucketsCount() const;

    friend ostream& operator<<(ostream& os, const hashMap& hS) {
        os << "{";
        for (size_t i = 0; i < hS.bucketCount; i++){
            os << hS.buckets[i];
                if (i + 1 != hS.bucketCount) {
                    os << ", " << endl;
                }
            }
            os << "}" << endl;
        return os;
    }

    List<Pair>& operator[](size_t index) const {
        if (index >= this->bucketCount) {
            throw std::out_of_range("Index out of range");
        }
        return this->buckets[index];
    }

};

#endif //HASHMAP_H
