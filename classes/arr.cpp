#include "arr.h"

arr<string> splitToArr(const string &input, const char delimiter){
    string word;
    arr<string> output;
    for (auto ch : input){
        if (ch == delimiter) {
            output.push_back(word);
            word = "";
        }
        else{
            word += ch;
        }
    }
    if (word != ""){
        output.push_back(word);
    }
    return output;
}

arr<string> splitToArr(const string& input, const string& delimiter){
    string word;
    arr<string> output;
    bool isDelim;
    int j;
    for (int i = 0; i < input.size(); ++i){
        if (input[i] == delimiter[0]){
            isDelim = true;
            for (j = 0; j < delimiter.size(); ++j){
                if (delimiter[j] != input[i + j]) isDelim = false;
            }
            if (isDelim){
                output.push_back(word);
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
        output.push_back(word);
    }
    return output;
}

string unsplit(const arr<string>& array, const char delimiter){
    string output;
    for (int i = 0; i < array.get_size(); ++i){
        if (i + 1 != array.get_size()) {
            output += array[i] + delimiter;
        }
        else {
            output += array[i];
        }
    }
    return output;
}
