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

        vector<bool> next_input_states;
        vector<bool> next_wire_states;
        vector<bool> next_output_states;

        Board map; // save wires connection scheme on board
    
    private:
        void powerTheWire(int id, bool status);
    
    public:
        void loadCircuit(const char* image_source);
        void simulate();
        void applyWireChanges();
        void applyOutputChanges();
        void applyInputChanges(uint index);
        void saveNewInputState(uint index, bool state);

        // constructors
        LogicWire(){};
        LogicWire(const char* image_source);
        
        void print(); // todo: remove (in future)
};