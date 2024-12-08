#ifndef NODE_H
#define NODE_H
#include <string>
#include <utility>

using std::string;

template <typename T>
class Node {
public:
    T value;
    Node* next;

    Node(T val, Node* following) : value(std::move(val)), next(following) {}
    explicit Node(T val) : value(std::move(val)), next(nullptr) {}
    Node() : value(T()), next(nullptr){}
};

template struct Node<int>;
template struct Node<string>;

#endif //NODE_H
