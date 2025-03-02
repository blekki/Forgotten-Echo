#include "pin.h"

using namespace std;

void Pin::setPower(bool power){
    this->power = power;
}

bool Pin::powerStatus(){
    return power;
}