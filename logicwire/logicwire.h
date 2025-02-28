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
    private:
        Board board;
        vector<Input> inputs;
        vector<Output> outputs;
        vector<bool> wires;
        vector<Gate> gates;

        Board map; // in the future: replace it to the LogicWire function
        
    public:
        LogicWire(const char* image_source);

        void simulate();
        void powerTheWire(int id);
        void print(); // in future i won't need it

        void powerTheInput(int id, bool status);
};