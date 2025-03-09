#include "input.h"

using namespace std;

// everything about local connection
void Input::setLocalConnection(uint wire_id){
    localConnection = wire_id;
}

uint Input::getLocalConnection(){
    return localConnection;
}

// everything about global connections
void Input::addGlobalConnection(Output* pin_id){
    globalConnections.push_back(pin_id);
}

Output* Input::getConnection(uint connection_id){
    return globalConnections.at(connection_id);
}

uint Input::getGlobalConnectionsCount(){
    return globalConnections.size();
}