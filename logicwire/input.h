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
        // vector<globalConnections;
        vector<Output*> globalConnections;
        // vector<Component*> classConnections;

    public:

        void setLocalConnection(uint wire_id);
        uint getLocalConnection();

        void addGlobalConnection(Output* pin_id);
        uint getGlobalConnectionsCount();
        Output* getConnection(uint connection_id);

        Input(uint id){
            this->id = id;
            localConnection = 0;
        }
};