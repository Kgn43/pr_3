#include "list.h"

template<typename T>
void List<T>::backInsert(T value) {
    ListNode<T>* newLast = new ListNode(value);
    if (last == nullptr){
        last = newLast;
        first = newLast;
    }
    else{
        newLast->previous = last;
        last->next = newLast;
        last = newLast;
    }
}

template<typename T>
void List<T>::headInsert(T value) {
    ListNode<T>* newFirst = new ListNode(value);
    if (last == nullptr){
        last = newFirst;
        first = newFirst;
    }
    else{
        first->previous = newFirst;
        newFirst->next = first;
        first = newFirst;
    }
}

template<typename T>
void List<T>::delLast() {
    if (this->first->next == nullptr){
        delete this->last;
        this->first = nullptr;
        this->last = nullptr;
    }
    else {
        last = last->previous;
        delete last->next;
        last->next = nullptr;
    }
}

template<typename T>
void List<T>::delFirst() {
    if (this->last->previous == nullptr){
        delete this->first;
        this->first = nullptr;
        this->last = nullptr;
    }
    else {
        this->first = this->first->next;
        delete this->first->previous;
        this->first->previous = nullptr;
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

List<Pair> splitToListPair(const string &input, const string& pairDelimiter, const char &keyValueDelimiter){
    string word;
    List<Pair> output;
    Pair currentPair;
    bool isDelim;
    int j;
    for (int i = 0; i < input.size(); ++i){
        if (input[i] == pairDelimiter[0]){
            isDelim = true;
            for (j = 0; j < pairDelimiter.size(); ++j){
                if (pairDelimiter[j] != input[i + j]) isDelim = false;
            }
            if (isDelim){
                output.backInsert(splitToPair(word, keyValueDelimiter));
                word = "";
                i += j - 1;
            }
            else {
                word += input[i];
            }
        }
        else {
            word += input[i];
        }
    }
    if (word != ""){
        output.backInsert(splitToPair(word, keyValueDelimiter));
    }
    return output;

}

string unSplitList(const List<string>& input, const char &delimiter){
    ListNode<string>* curr = input.first;
    string output;
    while (curr != nullptr){
        output += curr->value + delimiter;
        curr = curr->next;
    }
    return output;
}