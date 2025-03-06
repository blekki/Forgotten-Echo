#include "input.h"

using namespace std;

void Input::setLocalConnection(uint wire_id){
    localConnection = wire_id;
}

uint Input::getLocalConnection(){
    return localConnection;
}

void Input::addGlobalConnection(Output* pin_id){
    globalConnections.push_back(pin_id);
}