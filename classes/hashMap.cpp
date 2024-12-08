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
    List<Pair> oneBucket = this->buckets[thisHash];
    ListNode<Pair>* node = oneBucket.first;
    if (node->next == nullptr){ //остался один узел
            delete node;
            this->buckets[thisHash].first = nullptr;
            this->buckets[thisHash].last = nullptr;
            this->pairCount--;
            return;
    }
    while(node != nullptr){
        if (node->value.key == key){
            if (node->next != nullptr && node->previous != nullptr){ //удаляем не с краю
                node->next->previous = node->previous;
                node->previous->next = node->next;
                delete node;
                this->pairCount--;
                break;
            }
            if(node->next != nullptr){ //удалить первый узел
                oneBucket.delFirst();
                this->buckets[thisHash].first = this->buckets[thisHash].first->next;
                this->pairCount--;
                break;
            }
            oneBucket.delLast();
            this->pairCount--;
            break;
        }
        node = node->next;
    }
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

hashMap hMFromStr(const string& line){
    arr<string> pairs = splitToArr(line, "_NEXT_");
    hashMap output;
    for (size_t i = 0; i < pairs.size; ++i){
        output.insert(splitToPair(pairs[i], ','));
    }
    return output;
}

string strFromHM(hashMap input){
    string output;
    Pair pair1;
    while (input.pairCount != 0){
        pair1 = input.Get();
        output += unsplitFromPair(pair1, ',') + "_NEXT_";
        input.del(pair1.key);
    }
    return output;
}