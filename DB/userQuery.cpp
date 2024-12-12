#include "userQuery.h"


commands commandRequest(const std::string &input){
    if(input == "insert") return commands::Insert;
    if (input == "delete") return commands::Del;
    if (input == "select") return commands::Select;
    return commands::Wrong;
}


string selectRes() {
    string res;
    string part;
    if (ifstream file("crossJoin.csv"); file.is_open()) {
        while (getline(file, part)) {
            res += part + '\n';
        }
    }
    for (const auto ch : res) {
        if (ch != '\n') {
            res.pop_back();
            return res;
        }
    }
    return "";
}


string userQuery(const string& userQuery, const json& structureJSON){
    const arr<string> query = splitToArr(userQuery);
    if (query.get_size() == 0){
        return "query was not entered";
    }
    const commands comm = commandRequest(query[0]);
    try{
        switch (comm) {
            case Insert:
                insert(structureJSON, query);
                return "Success!";
            case Del:
                del(structureJSON, query);
                return "Success!";
            case Select:
                select(structureJSON, query);
                return selectRes();
            case Wrong:
                throw runtime_error("Wrong syntax");
        }
    }
    catch(exception& ex) {
        return ex.what();
    }
}
