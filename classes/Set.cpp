#include "Set.h"

size_t Set::hash(const int& value) const {
    int hash = 0;
    int buff = value;
    while (buff != 0) {
        hash += buff % 10;
        buff = buff / 10;
    }
    return hash % this->bucketCount;
}

void Set::coliseum() {
    Set newSet(this->bucketCount * 2);
    List<int> oneBucket;
    ListNode<int>* node;
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

void Set::insert(const int& value) {
    size_t thisHash = hash(value);
    bool isExist = false;
    for (auto i = this->buckets[thisHash].first; i != nullptr; i = i->next){
        if (i->value == value) isExist = true;
    }
    if (!isExist){
        this->buckets[thisHash].backInsert(value);
        this->pairCount++;
        if (this->bucketCount * 2 <= this->pairCount){
            coliseum();
        }
    }
    else {
        cout << "This value = " << value << " already in set" << endl;
    }
}

void Set::del(const int& value) {
    const size_t thisHash = hash(value);
    this->buckets[thisHash].delByVal(value);
    this->pairCount--;

}

bool Set::at(const int &value) const {
    const size_t thisHash = hash(value);
    ListNode<int>* node = this->buckets[thisHash].first;
    while(node != nullptr){
        if (node->value == value){
            return true;
        }
        node = node->next;
    }
    return false;
}

int Set::Get() const {
    for (size_t i = 0; i < this->buckets.size; ++i){
        if (this->buckets[i].first != nullptr) return this->buckets[i].first->value;
    }
    //error
    return 0;
}


size_t Set::size() const {
    return this->pairCount;
}

size_t Set::get_buckets() const {
    return this->bucketCount;
}

