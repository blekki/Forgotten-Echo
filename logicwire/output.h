#pragma once
#include <stdlib.h>

using namespace std;

class Output
{
    private:
        uint id;
        uint source = 0; // local conection (only inside circuit)
                         // "0" - sorce doesn't connected to wire
        uint drain;  // global connection

        bool power = true; //debug
    
    public:
        void setID(uint id);
        void setSource(uint drain);
        void setPower(bool power);

        uint getSource();
        bool powerStatus();
        
        Output(uint id) : id(id){}
};