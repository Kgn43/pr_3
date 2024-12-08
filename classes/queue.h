#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Node.h"
using namespace std;

template<typename T>
class Queue{
    Node<T>* head;
    Node<T>* tail;
    size_t size;
public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    Queue(const size_t len) : head(nullptr), tail(nullptr), size(0) {
        for (size_t i = 0; i < len; ++i) {
            this->push(T());
        }
    }

    void push(T val);
    void pop();
    T getFirst();
    size_t get_size() const;

    friend ostream& operator<<(ostream& os, const Queue& que) {
        Node<T>* curr = que.head;
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << " -> ";
            }
            curr = curr->next;
        }
        return os;
    }

    T& operator[](const size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        auto tmp = this->head;
        for (int i = 0; i != index; ++i) {
            tmp = tmp->next;
        }
        return tmp->value;
    }

};

template struct Queue<int>;
template struct Queue<string>;

#endif // QUEUE_H
