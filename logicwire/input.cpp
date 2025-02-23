#include "input.h"

using namespace std;

// a setup pack
void Input::setID(uint id){
    this->id = id;
}
void Input::setDrain(uint drain){
    this->drain = drain;
}
void Input::setPower(bool power){
    this->power = power;
}
//-------------

uint Input::getDrain(){
    return drain;
}

bool Input::powerStatus(){
    return power;
}