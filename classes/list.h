#ifndef LIST_H
#define LIST_H

#include "Pair.h"
#include <string>
#include <sstream>
using std::string, std::ostream;

template <typename T>
class ListNode {
public:
    T value;
    ListNode* next;
    ListNode* previous;

    ListNode(T val, ListNode* following, ListNode* prev) : value(val), next(following), previous(prev) {}
    ListNode(T val) : value(val), next(nullptr), previous(nullptr) {}
    ListNode() : value(T()), next(nullptr), previous(nullptr) {}
};


template <typename T>
class List{
    ListNode<T>* first;
    ListNode<T>* last;
    size_t size;
public:
    friend class hashMap;
    friend class Set;
    List(): first(nullptr), last(nullptr), size(0) {}

    List(size_t len) : first(nullptr), last(nullptr), size(0) {
        for (size_t i = 0; i < len; ++i) {
            this->headInsert(T());
        }
    }

    void headInsert(T value);
    void backInsert(T value);
    void delFirst();
    void delLast();
    void delByVal(T val);
    bool find(T value);
    size_t get_size() const;

    friend ostream& operator<<(ostream& os, const List<T>& ls) {
        ListNode<T> *curr = ls.first;
        os << "{";
        while (curr != nullptr){
            os << "[" << curr->value << "]";
            if (curr->next != nullptr) {
                os << " <=> ";
            }
            curr = curr->next;
        }
        os << "}";
        return os;
    }

    T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        auto tmp = this->first;
        for (int i = 0; i != index; ++i) {
            tmp = tmp->next;
        }
        return tmp->value;
    }

};

template struct List<Pair>;
template struct List<int>;
template struct List<string>;


#endif // LIST_H
