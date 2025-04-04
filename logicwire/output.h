#pragma once
#include <stdlib.h>
#include <vector>

#include "pin.h"

using namespace std;

class Output : public Pin
{
    private: 
        uint localConnection;
        // 1. first index [0] means pin connected to the ground of void
        // 2. save connection only to circuit

    public:
        void setLocalConnection(uint wire_id);
        uint getLocalConnection();

        Output(uint id){
            this->id = id;
            localConnection = 0;
        }

        Output(){
            Output(0);
        };
};