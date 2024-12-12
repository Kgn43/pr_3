#include "select.h"


///don't even try to understand what happend here


selectComm toSelectQuery(arr<string> query){
    if (query.get_size() <= 3){
        stringstream serr;
        serr << "wrong command: syntax error";
        throw runtime_error(serr.str());
    }
    if (query[1] == "from"){
        stringstream serr;
        serr << "wrong command: there is nothing to select";
        throw runtime_error(serr.str());
    }
    size_t fromPlc = 0;
    for (size_t i = 0; i < query.get_size(); ++i){
        if (query[i] == "from") fromPlc = i;
    }
    if (fromPlc == 0){
        stringstream serr;
        serr << "wrong command: there is no keyword\"from\'";
        throw runtime_error(serr.str());
    }
    if (query[fromPlc + 1] == "where"){
        stringstream serr;
        serr << "wrong command: there is no tables";
        throw runtime_error(serr.str());
    }
    size_t wherePlc = query.get_size();
    for (size_t i = 0; i < query.get_size(); ++i){
        if (query[i] == "where") wherePlc = i;
    }
    selectComm output;
    for (size_t i = 1; i < fromPlc; ++i){//записать условие
        output.columns.push_back(query[i]);
    }
    for (size_t i = fromPlc + 1; i < wherePlc; ++i){//записать условие
        output.tables.push_back(query[i]);
    }
    if (wherePlc == query.get_size()){
        output.condition = {};
    }
    else {
        for (size_t i = wherePlc + 1; i < query.get_size(); ++i){//записать условие
            output.condition.push_back(query[i]);
        }
    }
    return output;
}


bool isItColumn(json structure, const string& name) {
    for (json::iterator it = structure["structure"].begin(); it != structure["structure"].end(); ++it) {
        for (const auto & colName : it.value()){
            if (colName == name) return true;
        }
    }
    return false;
}


string findTableName(json structure, const string& name){
    for (json::iterator it = structure["structure"].begin(); it != structure["structure"].end(); ++it) {
        for (const auto & colName : it.value()){
            if (colName == name) return it.key();
        }
    }
    return "";
}


bool isItNum(const string& input){
    for (auto ch : input){
        if (ch > '9' || ch < '0') return false;
    }
    return true;
}


int getIndexFromStr(const string& input){
    string number;
    for (const auto& ch : input){
        if (ch == ';'){
            break;
        }
        else {
            number += ch;
        }
    }
    if (!isItNum(number)) return 0;
    return stoi(number);
}


arr<unoConditionPass> andCondAdd(const arr<unoConditionPass> &arr1, const unoConditionPass& condit){
    arr<unoConditionPass> output;
    bool isNotSame = true;
    for (size_t i = 0; i < arr1.get_size(); ++i) {
        if (arr1[i].tableName_1 == condit.tableName_1 && arr1[i].tableName_2 == condit.tableName_2) {
            isNotSame = false;
            unoConditionPass tmp;
            tmp.tableName_1 = arr1[i].tableName_1;
            tmp.tableName_2 = condit.tableName_2;
            for (size_t k = 0; k < arr1[i].pass.get_size(); ++k){
                for (size_t j = 0; j < condit.pass.get_size(); ++j){
                    if (arr1[i].pass[k] == condit.pass[j]){
                        tmp.pass.push_back(condit.pass[j]);
                        break;
                    }
                }
            }
            output.push_back(tmp);
        }
        else if(condit.tableName_2 == "SELF") {
            if (arr1[i].tableName_1 == condit.tableName_1) {
                isNotSame = false;
                unoConditionPass tmp;
                tmp.tableName_1 = arr1[i].tableName_1;
                tmp.tableName_2 = condit.tableName_2;
                for (size_t k = 0; k < arr1[i].pass.get_size(); ++k){
                    for (size_t j = 0; j < condit.pass.get_size(); ++j){
                        if (arr1[i].pass[k].key == condit.pass[j].key){
                            tmp.pass.push_back(condit.pass[j]);
                            break;
                        }
                    }
                }
                output.push_back(tmp);
            }
            else if (arr1[i].tableName_2 == condit.tableName_1) {
                isNotSame = false;
                unoConditionPass tmp;
                tmp.tableName_1 = arr1[i].tableName_1;
                tmp.tableName_2 = condit.tableName_2;
                for (size_t k = 0; k < arr1[i].pass.get_size(); ++k){
                    for (size_t j = 0; j < condit.pass.get_size(); ++j){
                        if (arr1[i].pass[k].value == condit.pass[j].key){
                            tmp.pass.push_back(condit.pass[j]);
                            break;
                        }
                    }
                }
                output.push_back(tmp);
            }
        }
        else if (arr1[i].tableName_1 == condit.tableName_1 && arr1[i].tableName_2 != condit.tableName_2) {
            isNotSame = false;
            unoConditionPass tmp1;
            tmp1.tableName_1 = arr1[i].tableName_1;
            tmp1.tableName_2 = arr1[i].tableName_2;
            unoConditionPass tmp2;
            tmp2.tableName_1 = condit.tableName_1;
            tmp2.tableName_2 = condit.tableName_2;
            for (size_t k = 0; k < arr1[i].pass.get_size(); ++k){
                for (size_t j = 0; j < condit.pass.get_size(); ++j){
                    if (arr1[i].pass[k].key == condit.pass[j].key){
                        tmp1.pass.push_back(arr1[i].pass[k]);
                        tmp2.pass.push_back(condit.pass[j]);
                        break;
                    }
                }
            }
            output.push_back(tmp1);
            output.push_back(tmp2);
        }
        else if (arr1[i].tableName_1 != condit.tableName_1 && arr1[i].tableName_2 == condit.tableName_2) {
            isNotSame = false;
            unoConditionPass tmp1;
            tmp1.tableName_1 = arr1[i].tableName_1;
            tmp1.tableName_2 = arr1[i].tableName_2;
            unoConditionPass tmp2;
            tmp2.tableName_1 = condit.tableName_1;
            tmp2.tableName_2 = condit.tableName_2;
            for (size_t k = 0; k < arr1[i].pass.get_size(); ++k){
                for (size_t j = 0; j < condit.pass.get_size(); ++j){
                    if (arr1[i].pass[k].value == condit.pass[j].value){
                        tmp1.pass.push_back(arr1[i].pass[k]);
                        tmp2.pass.push_back(condit.pass[j]);
                        break;
                    }
                }
            }
            output.push_back(tmp1);
            output.push_back(tmp2);
        }
        else if (arr1[i].tableName_1 == condit.tableName_2 && arr1[i].tableName_2 != condit.tableName_1) {
            isNotSame = false;
            unoConditionPass tmp1;
            tmp1.tableName_1 = arr1[i].tableName_1;
            tmp1.tableName_2 = arr1[i].tableName_2;
            unoConditionPass tmp2;
            tmp2.tableName_1 = condit.tableName_1;
            tmp2.tableName_2 = condit.tableName_2;
            for (size_t k = 0; k < arr1[i].pass.get_size(); ++k){
                for (size_t j = 0; j < condit.pass.get_size(); ++j){
                    if (arr1[i].pass[k].key == condit.pass[j].value){
                        tmp1.pass.push_back(arr1[i].pass[k]);
                        tmp2.pass.push_back(condit.pass[j]);
                        break;
                    }
                }
            }
            output.push_back(tmp1);
            output.push_back(tmp2);
        }
        else if (arr1[i].tableName_1 != condit.tableName_2 && arr1[i].tableName_2 == condit.tableName_1) {
            isNotSame = false;
            unoConditionPass tmp1;
            tmp1.tableName_1 = arr1[i].tableName_1;
            tmp1.tableName_2 = arr1[i].tableName_2;
            unoConditionPass tmp2;
            tmp2.tableName_1 = condit.tableName_1;
            tmp2.tableName_2 = condit.tableName_2;
            for (size_t k = 0; k < arr1[i].pass.get_size(); ++k){
                for (size_t j = 0; j < condit.pass.get_size(); ++j){
                    if (arr1[i].pass[k].value == condit.pass[j].key){
                        tmp1.pass.push_back(arr1[i].pass[k]);
                        tmp2.pass.push_back(condit.pass[j]);
                        break;
                    }
                }
            }
            output.push_back(tmp1);
            output.push_back(tmp2);
        }
        else {
            output.push_back(arr1[i]);
        }
    }
    if (isNotSame) {
        output.push_back(condit);
    }
    return output;
}



arr<unoConditionPass> orCondAdd(const arr<unoConditionPass> &arr1, const arr<unoConditionPass>& condit) {
    arr<unoConditionPass> output;
    for (size_t i = 0; i < arr1.get_size(); ++i) {
        output.push_back(arr1[i]);
    }
    bool isNotSame = true;
    for (size_t i = 0; i < arr1.get_size(); ++i) {
        int num;
        for (size_t h = 0; h < condit.get_size(); ++h) {
            num = h;
            if (output[i].tableName_1 == condit[h].tableName_1 && output[i].tableName_2 == condit[h].tableName_2) {
                isNotSame = false;
                for (size_t k = 0; k < output[i].pass.get_size(); ++k){
                    bool z = true;
                    for (size_t j = 0; j < condit[h].pass.get_size(); ++j){
                        if (output[i].pass[j] == condit[h].pass[k]){
                            z = false;
                            break;
                        }
                    }
                    if (z) {
                        output[i].pass.push_back(condit[h].pass[k]);
                    }
                }
            }
            else if(condit[h].tableName_2 == "SELF") {
                if (output[i].tableName_1 == condit[h].tableName_1) {
                    isNotSame = false;
                    for (size_t k = 0; k < output[i].pass.get_size(); ++k){
                        bool z = true;
                        for (size_t j = 0; j < condit[h].pass.get_size(); ++j){
                            if (output[i].pass[j].key == condit[h].pass[k].key){
                                z = false;
                                break;
                            }
                        }
                        if (z) {
                            int size = output[i].pass.get_size();
                            for (size_t j = 0; j < size; ++j) {
                                output[i].pass.push_back({condit[h].pass[k].key, output[i].pass[j].value});
                            }
                        }
                    }
                }
                else if (arr1[i].tableName_2 == condit[h].tableName_1) {
                    isNotSame = false;
                    for (size_t k = 0; k < output[i].pass.get_size(); ++k){
                        bool z = true;
                        for (size_t j = 0; j < condit[h].pass.get_size(); ++j){
                            if (output[i].pass[j].key == condit[h].pass[k].value){
                                z = false;
                                break;
                            }
                        }
                        if (z) {
                            int size = output[i].pass.get_size();
                            for (size_t j = 0; j < size; ++j) {
                                output[i].pass.push_back({output[i].pass[j].key, condit[h].pass[k].key});
                            }
                        }
                    }
                }
            }
            else {
                output.push_back(arr1[i]);
            }
        }
        if (isNotSame) {
            output.push_back(condit[num]);
        }
    }
    return output;
}


arr<unoConditionPass> connectCondition(const arr<arr<unoConditionPass>> &conditionTree){
    arr<unoConditionPass> outputArr;
    arr<unoConditionPass> andArr;
    for (size_t i = 0; i < conditionTree.get_size(); i++){
        for (size_t j = 0; j < conditionTree[i].get_size(); j++){
            if (j == 0){
                andArr.push_back(conditionTree[i][j]);
            }
            else{
                andArr = andCondAdd(andArr, conditionTree[i][j]);
            }
        }
        if (i == 0) {
            outputArr = andArr;
        }
        else {
            outputArr = orCondAdd(outputArr, andArr);
        }
    }
    return outputArr;
}


void createIndexes(const arr<arr<arr<string>>>& condition, arr<arr<unoConditionPass>>& indexes) {
    size_t size1 = condition.get_size();
    for (size_t i = 0; i < size1; ++i) {
        size_t size2 = condition[i].get_size();
        indexes[i].resize(size2);
    }
}


moreConditionPass appendCondition(arr<unoConditionPass> input) {
    size_t number = 0;
    for (size_t j = 0; j < input.get_size(); ++j) {
        if (!input[j].tableName_1.empty()) {
            number = j;
            break;
        }
    }
    moreConditionPass output(input[number].pass.get_size());
    if (input[0].tableName_2 != "SELF") {
        output.tableNames.push_back(input[number].tableName_1);
        output.tableNames.push_back(input[number].tableName_2);
        for (int i = 0; i < input[number].pass.get_size(); ++i) {
            output.pass[i].push_back(input[number].pass[i].key);
            output.pass[i].push_back(input[number].pass[i].value);
        }
    }
    else {
        output.tableNames.push_back(input[number].tableName_1);
        for (int j = 0; j < input[number].pass.get_size(); ++j) {
            output.pass[j].push_back(input[number].pass[j].key);
        }
    }
    for (int i = number + 1; i < input.get_size(); ++i) {
        if (input[i].tableName_2 != "SELF") {
            if (output.tableNames.find(input[i].tableName_1) == -1 && output.tableNames.find(input[i].tableName_2) != -1) {
                output.tableNames.push_back(input[i].tableName_1);
                int tabInd = output.tableNames.find(input[i].tableName_2);
                for (int j = 0; j < input[i].pass.get_size(); ++j) {
                    if (output.pass[j][tabInd] == input[i].pass[j].key) {
                        output.pass[j].push_back(input[i].pass[j].value);
                    }
                }
            }
            else if (output.tableNames.find(input[i].tableName_1) != -1 && output.tableNames.find(input[i].tableName_2) == -1) {
                output.tableNames.push_back(input[i].tableName_2);
                int tabInd = output.tableNames.find(input[i].tableName_1);
                for (int j = 0; j < input[i].pass.get_size(); ++j) {
                    if (output.pass[j][tabInd] == input[i].pass[j].value) {
                        output.pass[j].push_back(input[i].pass[j].key);
                    }
                }
            }
            else if (output.tableNames.find(input[i].tableName_1) == -1 && output.tableNames.find(input[i].tableName_2) == -1) {
                output.tableNames.push_back(input[i].tableName_1);
                output.tableNames.push_back(input[i].tableName_2);
                for (int j = 0; j < input[i].pass.get_size(); ++j) {
                    output.pass[j].push_back(input[i].pass[j].key);
                    output.pass[j].push_back(input[i].pass[j].value);
                }
            }
        }
        else {
            output.tableNames.push_back(input[i].tableName_1);
            for (int j = 0; j < input[i].pass.get_size(); ++j) {
                output.pass[j].push_back(input[i].pass[j].key);
            }
        }
    }
    return output;
}


moreConditionPass getPassNum(const json& structure, const arr<arr<arr<string>>>& condition){
    arr<arr<unoConditionPass>> indexes(condition.get_size());
    createIndexes(condition, indexes);
    string firstOperand;
    string secondOperand;
    string oper;
    ifstream firstStream;
    ifstream secondStream;
    string table1Name;
    string table2Name;
    string wayToTable;
    int firstCurrentPk;
    int secondCurrentPk;
    string firstPath;
    string secondPath;
    string firstGottenLine;
    string secondGottenLine;
    arr<string> firstSplitedLine;
    arr<string> secondSplitedLine;
    arr<string> firstTableHeaders;
    arr<string> secondTableHeaders;
    size_t firstHeaderNumber;
    size_t secondHeaderNumber;
    for (size_t i = 0; i < condition.get_size(); ++i){
        for (size_t j = 0; j < condition[i].get_size(); ++j){
            if (condition[i][j].get_size() != 3){
                stringstream serr;
                serr << "wrong condition";
                throw runtime_error(serr.str());
            }
            firstOperand = condition[i][j][0];
            oper = condition[i][j][1];
            secondOperand = condition[i][j][2];
            if (isItColumn(structure, secondOperand)){
                if (!isItColumn(structure, firstOperand)){
                    stringstream serr;
                    serr << "wrong table name";
                    throw runtime_error(serr.str());
                }
                table1Name = findTableName(structure, firstOperand);//находим имя таблицы
                tableCheck(table1Name, structure);//проверяем на случай отсутствия
                table2Name = findTableName(structure, secondOperand);//находим имя таблицы
                tableCheck(table2Name, structure);//проверяем на случай отсутствия
                firstPath = static_cast<string>(structure["name"]) + "/" + table1Name + "/" + table1Name;// уже не директории!!
                secondPath = static_cast<string>(structure["name"]) + "/" + table2Name + "/" + table2Name;
                firstCurrentPk = getCurrPk(firstPath); //текущий Pk1
                secondCurrentPk = getCurrPk(secondPath); //текущий Pk2
                //для всех файлов таблиц
                for (int k = 0; k <= firstCurrentPk / static_cast<int>(structure["tuples_limit"]) && k <= secondCurrentPk / static_cast<int>(structure["tuples_limit"]); ++k){
                    if (k != 0){//в каком мы файле?
                        wayToTable = "_" + to_string(i) + ".csv";
                    }
                    else {
                        wayToTable = ".csv";
                    }
                    //открываем потоки чтения файлов таблиц
                    firstStream.open(firstPath + wayToTable);
                    //разбиваем заголовки на массив
                    firstTableHeaders = getHeaders(firstPath + wayToTable);
                    secondTableHeaders = getHeaders(secondPath + wayToTable);
                    //находим в этих заголовках индекс колонки из проверяемого условия
                    firstHeaderNumber = firstTableHeaders.find(firstOperand);
                    secondHeaderNumber = secondTableHeaders.find(secondOperand);
                    //считываем строки пока можем
                    indexes[i][j].tableName_1 = table1Name;
                    indexes[i][j].tableName_2 = table2Name;
                    while (getline(firstStream, firstGottenLine)){
                        if (firstGottenLine.empty() || firstGottenLine == " ") continue;
                        secondStream.open(secondPath + wayToTable);
                        while (getline(secondStream, secondGottenLine)) {
                            if (secondGottenLine.empty() || secondGottenLine == " ") continue;
                            if (oper == "="){
                                //разбиваем строку для обращения по индексу колонки
                                firstSplitedLine = splitToArr(firstGottenLine, ';');
                                secondSplitedLine = splitToArr(secondGottenLine, ';');
                                //cout << firstSplitedLine << " " << firstHeaderNumber << endl << secondSplitedLine << secondHeaderNumber << endl;
                                //проверка ОДНОГО условия
                                if (firstSplitedLine[firstHeaderNumber] == secondSplitedLine[secondHeaderNumber]) {
                                    indexes[i][j].pass.push_back({getIndexFromStr(firstGottenLine), getIndexFromStr(secondGottenLine)});
                                }
                            }
                            else {
                                stringstream serr;
                                serr << "wrong operator";
                                throw runtime_error(serr.str());
                            }
                        }
                        secondStream.close();
                    }
                    firstStream.close();
                }
            }
            else {
                table1Name = findTableName(structure, firstOperand);//находим имя таблицы
                tableCheck(table1Name, structure);//проверяем на случай отсутствия
                firstPath = static_cast<string>(structure["name"]) + "/" + table1Name + "/" + table1Name;// уже не директория!!
                firstCurrentPk = getCurrPk(firstPath); //текущий Pk1
                //для всех файлов таблиц
                for (int k = 0; k <= firstCurrentPk / static_cast<int>(structure["tuples_limit"]); ++k){
                    if (k != 0){//в каком мы файле?
                        wayToTable = "_" + to_string(i) + ".csv";
                    }
                    else {
                        wayToTable = ".csv";
                    }
                    //открываем потоки чтения файлов таблиц
                    firstStream.open(firstPath + wayToTable);
                    //разбиваем заголовки на массив
                    firstTableHeaders = getHeaders(firstPath + wayToTable);
                    //находим в этих заголовках индекс колонки из проверяемого условия
                    firstHeaderNumber = firstTableHeaders.find(firstOperand);
                    //считываем строки пока можем
                    indexes[i][j].tableName_1 = table1Name;
                    indexes[i][j].tableName_2 = "SELF";
                    while (getline(firstStream, firstGottenLine)){
                        if (firstGottenLine.empty() || firstGottenLine == " ") continue;
                        if (oper == "="){
                            //разбиваем строку для обращения по индексу колонки
                            firstSplitedLine = splitToArr(firstGottenLine, ';');
                            //проверка ОДНОГО условия
                            if (firstSplitedLine[firstHeaderNumber] == secondOperand) {
                                indexes[i][j].pass.push_back({getIndexFromStr(firstGottenLine), -1});
                            }
                        }
                        else {
                            stringstream serr;
                            serr << "wrong operator";
                            throw runtime_error(serr.str());
                        }
                    }
                    firstStream.close();
                }
            }
        }
    }
    // cout << indexes << endl;
    arr<unoConditionPass> pass = connectCondition(indexes);
    // cout << pass << endl;
    moreConditionPass connected = appendCondition(pass);
    return connected;
}


string getValueByIndex(json structure, const string& tableName, const string& columnName, int index){
    string path = static_cast<string>(structure["name"]) + "/" + tableName + "/" + tableName;
    arr<string> headers = getHeaders(path + ".csv");
    size_t ind = headers.find(columnName);
    if (ind == -1) {
        return "";
    }
    if (index >= static_cast<int>(structure["tuples_limit"])){//в каком мы файле?
        path += "_" + to_string(index/static_cast<int>(structure["tuples_limit"])) + ".csv";
    }
    else {
        path += ".csv";
    }
    ifstream stream;
    string gottenLine;
    stream.open(path);
    arr<string> splitedLine;
    while (getline(stream, gottenLine)){
        if (gottenLine.empty() || gottenLine == " ") continue;
        if (getIndexFromStr(gottenLine) == index){
            splitedLine = splitToArr(gottenLine, ';');
            return splitedLine[ind];
        }
    }
    return "";
}


string getValueFromColumnByIndex(json structure, const string& tableName, const string &columnsName, const int index) {
    string path = static_cast<string>(structure["name"]) + "/" + tableName + "/" + tableName;
    arr<string> headers = getHeaders(path + ".csv");
    int ind = headers.find(columnsName);
    if (ind == -1) {
        return "";
    }
    if (index >= static_cast<int>(structure["tuples_limit"])){//в каком мы файле?
        path += "_" + to_string((index/static_cast<int>(structure["tuples_limit"]))) + ".csv";
    }
    else {
        path += ".csv";
    }
    ifstream stream;
    string gottenLine;
    stream.open(path);
    arr<string> splitedLine;
    while (getline(stream, gottenLine)){
        if (gottenLine.empty() || gottenLine == " ") continue;
        if (getIndexFromStr(gottenLine) == index){
            splitedLine = splitToArr(gottenLine, ';');
            return splitedLine[ind];
        }
    }
    return "";
}


void xJoinOneTabe(const json &structure, const selectComm &query) {
    string file_path = static_cast<string>(structure["name"]) + "/" + query.tables[0] + "/" + query.tables[0];
    const arr<string> headers = getHeaders(file_path + ".csv");
    arr<size_t> indexes;
    for (int i = 0; i < query.columns.get_size(); i++) {
        indexes.push_back(headers.find(query.columns[i]));
    }
    if (indexes[0] == -1) {
            throw runtime_error("wrong table or column name");
    }
    for (int i = 0; i < indexes.get_size(); i++) {
        if (indexes[i] == -1) {
            throw runtime_error("wrong table or column name");
        }
    }
    // cout << indexes << endl;
    ifstream stream;
    string gottenLine;
    int pk = getCurrPk(file_path);
    for (int j = 0; j <= pk / static_cast<int>(structure["tuples_limit"]); ++j) {
        if (j != 0) {
            file_path += "_" + to_string(j) + ".csv";
            stream.open(file_path);
        }
        else {
            file_path += ".csv";
            stream.open(file_path);
            string headers2;
            getline(stream, gottenLine);
        }
        arr<string> splitedLine;
        ofstream out("crossJoin.csv");
        while (getline(stream, gottenLine)){
            if (gottenLine.empty() || gottenLine == " ") continue;
            splitedLine = splitToArr(gottenLine, ';');
            for (int i = 0; i < indexes.get_size(); i++) {
                out << splitedLine[indexes[i]];
                if (1 + i != indexes.get_size()) {
                    out << ';';
                }
            }
            out << '\n';
        }
        out.close();
    }
}


void DecardJoin(const selectComm &query, const string &filePath1, const string &filePath2) {
    const arr<string> headers1 = getHeaders(filePath1 + ".csv");
    const arr<string> headers2 = getHeaders(filePath2 + ".csv");
    arr<size_t> indexes1;
    arr<size_t> indexes2;
    for (int i = 0; i < query.columns.get_size(); i++) {
        indexes1.push_back(headers1.find(query.columns[i]));
    }
    for (int i = 0; i < query.columns.get_size(); i++) {
        indexes2.push_back(headers2.find(query.columns[i]));
    }
    ifstream stream1;
    ifstream stream2;
    string firstGottenLine;
    string secondGottenLine;
    stream1.open(filePath1);
    stream2.open(filePath2);
    arr<string> firstsplitedLine;
    arr<string> secondsplitedLine;
    ofstream out("xjoinTmp.csv");
    while (getline(stream1, firstGottenLine)){
        if (firstGottenLine.empty() || firstGottenLine == " ") continue;
        firstsplitedLine = splitToArr(firstGottenLine, ';');
        while (getline(stream2, secondGottenLine)){
            if (secondGottenLine.empty() || secondGottenLine == " ") continue;
            secondsplitedLine = splitToArr(secondGottenLine, ';');
            for (int i = 0; i < indexes1.get_size(); i++) {
                out << firstsplitedLine[indexes1[i]];
                if (1 + i != indexes1.get_size()) {
                    out << ';';
                }
                for (int j = 0; j < indexes2.get_size(); j++) {
                    out << secondsplitedLine[indexes2[j]];
                    if (1 + i != indexes2.get_size()) {
                        out << ';';
                    }
                }
                out << '\n';
            }
        }
    }
    stream1.close();
    stream2.close();
    out.close();
    stream1.open("xjoinTmp.csv");
    out.open("crossJoin.csv");
    while (getline(stream1, firstGottenLine)) {
        out << firstGottenLine;
    }
}


void select(const json& structure, arr<string> inputQuery){
    //cout << inputQuery << endl;
    selectComm query = toSelectQuery(inputQuery);//получаем имена таблиц, колонки и условия для выборки
     // cout << query.columns << " " << query.tables <<" "<< query.condition << endl;
    for (size_t i = 0; i < query.tables.get_size(); ++i){//для всех таблиц проверяем их существование
        tableCheck(query.tables[i], structure);
    }
    if (query.condition.get_size() != 0){
        arr<string> cond; //младший сын
        cond = splitToArr(unsplit(query.condition), " OR ");
        arr<arr<string>> condit; //средний сын
        for (size_t i = 0; i < cond.get_size(); ++i){
            condit.push_back(splitToArr(cond[i], " AND "));
        }
        arr<arr<arr<string>>> condition(condit.get_size()); //старший сын
        for (size_t i = 0; i < condit.get_size(); ++i){
            for (size_t j = 0; j < condit[i].get_size(); ++j){
                condition[i].push_back(splitToArr(condit[i][j], ' '));
            }
        }
        moreConditionPass nums;
        for (size_t i = 0; i < query.tables.get_size(); ++i){
            lock(static_cast<string>(structure["name"]) + "/" + query.tables[i] + "/" + query.tables[i]);
        }
        try {
            nums = getPassNum(structure, condition);
        } catch (exception& ex) {
            for (size_t i = 0; i < query.tables.get_size(); ++i){
                unlock(static_cast<string>(structure["name"]) + "/" + query.tables[i] + "/" + query.tables[i]);
            }
            throw runtime_error(ex.what());
        }
        string firstWord;
        string secondWord;
        ofstream crossJoin("crossJoin.csv");
        // cout << nums.tableNames << " " << nums.pass << endl << endl;
        try {
            for (size_t i = 0; i < nums.pass.get_size(); ++i) {
                for (size_t j = 0; j < nums.pass[i].get_size(); ++j) {
                    for (int k = 0; k < query.columns.get_size(); ++k) {
                        if (string val = getValueByIndex(structure, findTableName(structure, query.columns[k]), query.columns[k], nums.pass[i][nums.tableNames.find(findTableName(structure, query.columns[k]))]); !val.empty()) {
                            crossJoin << val;
                            if (k + 1 != query.columns.get_size()) crossJoin << ';';
                        }
                    }
                }
                crossJoin << '\n';
            }
        }
        catch (exception& ex) {
            for (size_t i = 0; i < query.tables.get_size(); ++i){
                unlock(static_cast<string>(structure["name"]) + "/" + query.tables[i] + "/" + query.tables[i]);
            }
            throw runtime_error(ex.what());
        }
        for (size_t i = 0; i < query.tables.get_size(); ++i){
            unlock(static_cast<string>(structure["name"]) + "/" + query.tables[i] + "/" + query.tables[i]);
        }
        crossJoin.close();
    }
    else{
        if (query.tables.get_size() == 1) {
            xJoinOneTabe(structure ,query);
            return;
        }
        DecardJoin(query, query.tables[0] + "/" + query.tables[0] + "/" + query.tables[0], query.tables[1] + "/" + query.tables[1] + "/" + query.tables[1]);
        for (int i = 2; i < query.tables.get_size(); ++i) {
            DecardJoin(query, query.tables[i] + "/" + query.tables[i] + "/" + query.tables[i], "xjoinTmp.csv");
        }
    }
}
