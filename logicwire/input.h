#pragma once
#include <stdlib.h>
#include <vector>

#include "pin.h"
#include "output.h"

using namespace std;

class Input: public Pin
{
    private:
        uint localConnection; // zero means it doesn't connected
        vector<Output*> globalConnections;

    public:

        void setLocalConnection(uint wire_id);
        uint getLocalConnection();
        void addGlobalConnection(Output* pin_id);

        uint getGlobalConnectionsCount(){
            return globalConnections.size();
        }

        Output* getConnection(uint id){
            return globalConnections.at(id);
        }

        Input(uint id){
            this->id = id;
            localConnection = 0;
            // globalConnections.push_back(nullptr);
        }
};