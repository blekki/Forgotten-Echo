#include "input.h"

using namespace std;

void Input::setLocalConnection(uint wire_id){
    globalConnections.at(0) = wire_id;
}

uint Input::getLocalConnection(){
    return globalConnections.at(0);
}

void Input::addGlobalConnection(uint pin_id){
    globalConnections.push_back(pin_id);
}