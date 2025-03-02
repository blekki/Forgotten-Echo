#pragma once
#include <vector>
#include <functional>

#include "board.h"
#include "gate.h"
#include "input.h"
#include "output.h"


using namespace std;

class LogicWire
{
    protected:
        // curcuits
        Board board;
        vector<Input> inputs;
        vector<bool> wires;
        vector<Gate> gates;
        vector<Output> outputs;

        Board map; // in the future: replace it to the LogicWire function
        
    public:
        void loadCircuit(const char* image_source);
        void simulate();
        
        // circuits mustn't have open gate for user
        void powerTheWire(int id); //todo: remove (in future)
        void print(); // todo: remove (in future)
        void powerTheInput(int id, bool status); // todo: remove (in far future)
};