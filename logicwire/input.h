#pragma once
#include <stdlib.h>

using namespace std;

class Input
{
    private:
        uint id;
        uint source; // "0" id means wire connected to satellited
        uint drain = 0; // "0" - drain connected to free space on circuit

        bool power = true; //debug
    
    public:
        void setID(uint id);
        void setDrain(uint drain);
        void setPower(bool power);

        uint getDrain();
        bool powerStatus();
        
        Input(uint id) : id(id){}
};