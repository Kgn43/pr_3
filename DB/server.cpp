#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>//sleep func
#include <future>
#include <mutex>
#include <thread>
#include <arpa/inet.h>

#include "../ip.h"
#include "makeStructure.h"
#include "userQuery.h"


void requestProcessing(const int clientSocket, const sockaddr_in& clientAddress, const nlohmann::json& structure) {
    mutex userMutex;
    char receive[1024] = {};
    string sending;
    bool isExit = false;
    while (!isExit) {
        lock_guard<mutex> guard(userMutex);
        bzero(receive, 1024);
        const ssize_t userRead = read(clientSocket, receive, 1024);
        if (userRead <= 0) {
            cerr << "client[" << clientAddress.sin_addr.s_addr << "] disconnected\n";
            isExit = true;
            continue;
        }
        cout << "received from [" << clientAddress.sin_addr.s_addr << "] \"" << receive << '\"' << endl;
        if (receive == "disconnect") {
            isExit = true;
            continue;
        }
        string result = userQuery(receive ,structure);
        if (result.empty() || result == "") {
            result = "EMPTY";
        }
        cout << "send to [" << clientAddress.sin_addr.s_addr << "] \"" << result << '\"' << endl;
        send(clientSocket, result.c_str(), result.size(), 0);
    }
    close(clientSocket);
}


void startServer(const json& structureJSON) {
    const int server = socket(AF_INET, SOCK_STREAM, 0);//file descriptor
    if (server == -1) {
        cerr << "Socket creation error" << endl;
        return;
    }
    sockaddr_in address{}; //IPV4 protocol structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP); //any = 0.0.0.0
    address.sin_port = htons(7432);//host to net short
    //close(server);
    if (bind(server, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) < 0) {
        cerr << "Binding error" << endl;
        return;
    }

    if (listen(server, 10) == -1) {
        cerr << "Socket listening error" << endl;
        return;
    }

    cout << "Server started" << endl;

    sockaddr_in clientAddress{};
    socklen_t clientAddrLen = sizeof(clientAddress);
    while (true){
        int clientSocket = accept(server, reinterpret_cast<struct sockaddr *>(&clientAddress), &clientAddrLen);
        if(clientSocket == -1){
            cout << "connection fail" << endl;
            continue;
        }
        cout << "Client[" << clientAddress.sin_addr.s_addr << "] was connected" << endl;
        thread( requestProcessing, clientSocket, clientAddress, structureJSON).detach();
    }
    close(server);
}


int main() {
    string strcrt = "../DB/strktr.json";
    json structureJSON;
    try{
        ifstream jsonFile (strcrt);
        if (!jsonFile.is_open()) throw runtime_error("The structure file does not exist");
        structureJSON = json::parse(jsonFile);
        jsonFile.close();
        makeStructure(structureJSON);
        lotNames(structureJSON);
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
        return -1;
    }
    startServer(structureJSON);
    return 0;
}
