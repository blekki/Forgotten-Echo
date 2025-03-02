#pragma once
#include <stdlib.h>
#include <vector>

#include "pin.h"

using namespace std;

class Input: public Pin
{
    private:
    
    public:
        void setDrain(uint drain);
        uint getDrain();
        
        Input(uint id){
            this->id = id;
            connections.push_back(0);
        }
};