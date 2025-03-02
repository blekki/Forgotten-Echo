#pragma once
#include "stdlib.h"
#include <vector>

using namespace std;

class Pin
{
    protected:
        uint id;
        bool power = false;

        uint source = 0; //"0" means without connection
        uint drain = 0;
        vector<uint> connections; // zero index means wire connected to the "ground"
    
    public:
        void setID(uint id);
        void setPower(bool power);
        bool powerStatus();

        void addConnection(uint output_id){
            connections.push_back(output_id);
        }
};