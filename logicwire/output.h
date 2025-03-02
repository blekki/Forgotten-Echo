#pragma once
#include <stdlib.h>
#include <vector>

#include "pin.h"

using namespace std;

class Output : public Pin
{
    public:
        void setSource(uint source);
        uint getSource();
        
        Output(uint id){
            this->id = id;
            connections.push_back(0);
        }
};