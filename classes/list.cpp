#include "list.h"

template<typename T>
void List<T>::backInsert(T value) {
    ListNode<T>* newLast = new ListNode(value);
    if (last == nullptr){
        last = newLast;
        first = newLast;
        ++this->size;
    }
    else{
        newLast->previous = last;
        last->next = newLast;
        last = newLast;
        ++this->size;
    }
}

template<typename T>
void List<T>::headInsert(T value) {
    ListNode<T>* newFirst = new ListNode(value);
    if (last == nullptr){
        last = newFirst;
        first = newFirst;
        ++this->size;
    }
    else{
        first->previous = newFirst;
        newFirst->next = first;
        first = newFirst;
        ++this->size;
    }
}

template<typename T>
void List<T>::delLast() {
    if (this->first->next == nullptr){
        delete this->last;
        this->first = nullptr;
        this->last = nullptr;
        --this->size;
    }
    else {
        last = last->previous;
        delete last->next;
        last->next = nullptr;
        --this->size;
    }
}

template<typename T>
void List<T>::delFirst() {
    if (this->last->previous == nullptr){
        delete this->first;
        this->first = nullptr;
        this->last = nullptr;
        --this->size;
    }
    else {
        this->first = this->first->next;
        delete this->first->previous;
        this->first->previous = nullptr;
        --this->size;
    }
}

template<typename T>
bool List<T>::find(T value) {
    ListNode<T> *tmp = first;
    while (tmp != nullptr){
        if (tmp->value == value){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

template<typename T>
void List<T>::delByVal(T val) {
    if (this->first->value == val) {
        delFirst();
        return;
    }
    if (this->last->value == val) {
        delLast();
        return;
    }
    ListNode<T> *tmp = first;
    while (tmp != nullptr){
        if (tmp->value == val){
            tmp->next->previous = tmp->previous;
            tmp->previous->next = tmp->next;
            delete tmp;
            --this->size;
            return;
        }
        tmp = tmp->next;
    }
    std::stringstream serr;
    serr << "Not found " << val;
    throw std::runtime_error(serr.str());
}

List<string> splitToList(const string &input, const char &delimiter){
    string word;
    List<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.backInsert(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (word != ""){
        output.backInsert(word);
    }
    return output;
}

template<typename T>
size_t List<T>::get_size() const {
    return this->size;
}
