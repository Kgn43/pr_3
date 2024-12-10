#ifndef PAIR_H
#define PAIR_H

template <typename T, typename U>
class Pair{
public:
    T key;
    U value;

    Pair(): key(0), value(0) {};
    Pair(T k, U v): key(k), value(v) {};

    bool operator==(const Pair& other) const {
        return (key == other.key && value == other.value);
    }

    friend ostream& operator<<(ostream& os, const Pair& pr) {
        os << pr.key << ", " << pr.value;
        return os;
    }

};
#endif //PAIR_H
