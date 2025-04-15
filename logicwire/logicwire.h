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
        void applyChanges();

        void applyNextInputState(uint index){
            inputs[index].setPower(next_input_states[index]);
        }
        void applyNextInputState(){
            for (uint a = 0; a < inputs.size(); a++) {
                inputs[a].setPower(next_input_states[a]);
            }
        }

        void pushNextInputState(uint index, bool state){
            next_input_states.at(index) = state;
        }

        // constructors
        LogicWire(){};
        LogicWire(const char* image_source);
        
        // circuits mustn't have open gate for user
        void print(); // todo: remove (in future)
};