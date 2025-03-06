#pragma once
#include <stdlib.h>
#include <vector>

#include "pin.h"

using namespace std;

class Input: public Pin
{
    private:
        uint localConnection;
        vector<uint> globalConnections;
        // zero means it doesn't connected

    public:

        void setLocalConnection(uint wire_id);
        uint getLocalConnection();
        void addGlobalConnection(uint pin_id);

        Input(uint id){
            this->id = id;
            localConnection = 0;
            globalConnections.push_back(0);
        }
};