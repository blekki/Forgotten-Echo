#pragma once
#include "stdlib.h"
#include <vector>

using namespace std;

class Pin
{
    protected:
        uint id;
        bool power;
    
    public:
        void newId(uint id);
        uint getId();
        void setPower(bool power);
        bool checkPower();

        Pin(){
            power = false; // first power state always is FALSE
        }
};