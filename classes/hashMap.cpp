#include "hashMap.h"

size_t hashMap::hash(const string& key) const {
    int hash = 0;
    for (auto ch : key){
        hash += static_cast<int>(ch);
    }
    return hash % this->bucketCount;
}

void hashMap::coliseum() {
    hashMap newSet(this->bucketCount + 1);
    List<Pair> oneBucket;
    ListNode<Pair>* node;
    for (size_t i = 0; i < this->buckets.size; ++i){
        oneBucket = this->buckets[i];
        node = oneBucket.first;
        while(node != nullptr){
            newSet.insert(node->value);
            node = node->next;
        }
    }
    buckets = newSet.buckets;
    bucketCount = newSet.bucketCount;
    pairCount = newSet.pairCount;
}

void hashMap::insert(const string& key, const string& value) {
    size_t thisHash = hash(key);
    bool isExist = false;
    for (auto i = this->buckets[thisHash].first; i != nullptr; i = i->next){
        if (i->value.key == key) isExist = true;
    }
    if (!isExist){
        Pair inserted(key, value);
        this->buckets[thisHash].backInsert(inserted);
        this->pairCount++;
        if (this->bucketCount * this->bucketCount <= this->pairCount){
            coliseum();
        }
    }
    else {
        cout << "Pair with key " << key << " already in this hashMap" << endl;
    }
}

void hashMap::insert(const Pair& input) {
    size_t thisHash = hash(input.key);
    bool isExist = false;
    for (auto i = this->buckets[thisHash].first; i != nullptr; i = i->next){
        if (i->value.key == input.key) isExist = true;
    }
    if (!isExist){
        this->buckets[thisHash].backInsert(input);
        this->pairCount++;
        if (this->bucketCount * this->bucketCount <= this->pairCount){
            coliseum();
        }
    }
    else {
        cout << "Pair with key " << input.key << " already in this hashMap" << endl;
    }
}

void hashMap::del(const string& key) {
    size_t thisHash = hash(key);
    this->buckets[thisHash].delByVal({key, key});
    --this->pairCount;
}

Pair hashMap::Get(const string &key) const {
    size_t thisHash = hash(key);
    ListNode<Pair>* node = this->buckets[thisHash].first;
    while(node != nullptr){
        if (node->value.key == key){
            return node->value;
        }
        node = node->next;
    }
    return {};
}

Pair hashMap::Get() const {
    for (size_t i = 0; i < this->buckets.size; ++i){
        if (this->buckets[i].first != nullptr) return this->buckets[i].first->value;
    }
    return {};
}


size_t hashMap::get_size() const {
    return this->pairCount;
}

size_t hashMap::get_bucketsCount() const {
    return this->bucketCount;
}

