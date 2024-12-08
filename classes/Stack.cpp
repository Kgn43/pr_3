#include "Stack.h"

template <typename T>
void Stack<T>::push(T val) {
    Node<T>* newElement = new Node{val, this->head};
    this->head = newElement;
    ++this->size;
}

template <typename T>
void Stack<T>::pop() {
    if (this->head != nullptr) {
        Node<T>* tmp = this->head;
        this->head = head->next;
        delete tmp;
        --this->size;
    }
}

template <typename T>
T Stack<T>::getLast() {
    return this->head->value;
}

template<typename T>
size_t Stack<T>::get_size() const {
    return this->size;
}