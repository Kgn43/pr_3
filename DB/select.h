#ifndef SELECT_H
#define SELECT_H

#include <string>
#include "nlohmann/json.hpp"
#include "../classes/arr.h"
#include "../classes/Pair.h"
#include "common.h"


struct selectComm{
    arr<string> tables;
    arr<string> columns;
    arr<string> condition;

};


struct unoConditionPass{
    string tableName_1;
    string tableName_2;
    arr<Pair<int, int>> pass;

    friend ostream& operator<<(ostream& os, const unoConditionPass& arr) {
        os << "{";
        os << arr.tableName_1 << ", " << arr.tableName_2;
        os << arr.pass;
        os << "}";
        return os;
    }
};


struct moreConditionPass {
    arr<string> tableNames;
    arr<arr<int>> pass;

    moreConditionPass()= default;

    explicit moreConditionPass(size_t n) {
        pass.resize(n);
    }

    friend ostream& operator<<(ostream& os, const moreConditionPass& arr) {
        os << "{";
        os << arr.tableNames << " ";
        os << arr.pass;
        os << "}";
        return os;
    }

};


void select(const json& structure, arr<string> inputQuery);
string getValueByIndex(json structure, const string& tableName, const arr<string>& columnsName, int index);
//arr<moreConditionPass> getPassNum(const json& structure, const arr<arr<arr<string>>>& condition);
arr<int> connectCondition(const arr<arr<arr<int>>> &arr1);
arr<int> addIfNotUnic(arr<int> arr1, arr<int> arr2);
int getIndexFromStr(const string& input);
string findTableName(json structure, const string& name);
bool isItColumn(json structure, const string& name);
selectComm toSelectQuery(arr<string> query);

#endif //SELECT_H
