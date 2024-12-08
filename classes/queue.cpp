#include "queue.h"

template<typename T>
void Queue<T>::push(T val) {// вставляем в хвост
    Node<T>* newElement = new Node{val};
    if (this->head == nullptr) {
        this->head = newElement;
        this->tail = newElement;
        ++this->size;
    }
    else {
        this->tail->next = newElement;
        this->tail = newElement;
        ++this->size;
    }
}

template<typename T>
void Queue<T>::pop() { //удаляем с головы
    if (this->head == nullptr) return;
    auto tmpHead = this->head;
    this->head = this->head->next;
    delete tmpHead;
    --this->size;
}

template<typename T>
T Queue<T>::getFirst() {
    return this->head->value;
}

template<typename T>
size_t Queue<T>::get_size() const {
    return this->size;
}
