#pragma once
#include <stdlib.h>
#include <vector>

#include "logicwire.h"

using namespace std;

class Circuit
{
    private:
        vector<LogicWire> schemes;

    public:
        void simulation(){
            for (uint a = 0; a < schemes.size(); a++) {
                schemes[a].simulate();
            }
        }
};