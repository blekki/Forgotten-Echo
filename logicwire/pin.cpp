#include "pin.h"

using namespace std;

uint Pin::getId(){ // return Pin ID
    return this->id;
}

void Pin::setPower(bool power){
    this->power = power;
}

bool Pin::checkPower(){
    return power;
}