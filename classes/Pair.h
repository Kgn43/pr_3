#ifndef PAIR_H
#define PAIR_H

#include <string>
#include <sstream>

using std::string, std::ostream;

class Pair{
public:
    string key;
    string value;

    Pair(): key(""), value("") {};
    Pair(string k, string v): key(std::move(k)), value(std::move(v)) {};

    bool operator==(const Pair& other) const {
        return (key == other.key) && (value == other.value);
    }

    friend ostream& operator<<(ostream& os, const Pair& pr) {
        os << pr.key << ", " << pr.value;
        return os;
    }

};


Pair splitToPair(const string& inputLine,const char &delimiter);
string unsplitFromPair(const Pair& input, const char &delimiter);

#endif //PAIR_H
