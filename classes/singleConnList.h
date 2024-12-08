#ifndef SINGLECONNLIST_H
#define SINGLECONNLIST_H

#include <iostream>
#include "Node.h"

using namespace std;

template<typename T>
class sList {
    Node<T>* head;
    size_t size;
public:
    sList() : head(nullptr), size(0) {}

    void headInsert(T value);
    void backInsert(T value);
    void delFirst();
    void delLast();
    void delByVal(T val);
    bool find(T value) const;

    friend ostream& operator<<(ostream& os, const sList& ls) {
        Node<T> *curr = ls.head;
        os << "{";
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << ", ";
            }
            curr = curr->next;
        }
        os << "}";
        return os;
    }

    T& operator[](const size_t index) const {
        if (index >= this->size) {
            throw std::out_of_range("Index out of range");
        }
        auto tmp = this->head;
        for (int i = 0; i != index; ++i) {
            tmp = tmp->next;
        }
        return tmp->value;
    }

};

template struct sList<int>;
template struct sList<string>;

#endif // SINGLECONNLIST_H
