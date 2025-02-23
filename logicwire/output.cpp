#include "output.h"

using namespace std;

// a setup pack
void Output::setID(uint id){
    this->id = id;
}
void Output::setSource(uint source){
    this->source = source;
}
void Output::setPower(bool power){
    this->power = power;
}
//-------------

uint Output::getSource(){
    return source;
}

bool Output::powerStatus(){
    return power;
}