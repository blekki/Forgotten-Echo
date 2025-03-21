#pragma once
#include <vector>
#include "circuit.h"

using namespace std;

class System
{
    private:
        LogicWire space;
        vector<Circuit*> circuits;

    public:
        void simulate(){
            // satellites simulation
            for (vector<Circuit*>::iterator circuit_iter = circuits.begin(); circuit_iter != circuits.end(); circuit_iter++) {
                (*circuit_iter)->simulate();
                (*circuit_iter)->print(); // debug
            }

            // space signal simulation
            vector<bool> new_input_states;
            for (uint a = 0; a < space.getInputsCount(); a++) { // check every input connections
                new_input_states.push_back(false);
                
                Input* current_input_ptr = space.getInput(a);
                for (uint c = 0; c < current_input_ptr->getGlobalConnectionsCount(); c++) { // check every connection to the input
    
                    Output* current_output_ptr = current_input_ptr->getConnection(c);
                    if (current_output_ptr->checkPower()) {
                        new_input_states.at(a) = true;
                        break;
                    }
                }
                current_input_ptr->setPower(new_input_states.at(a));
            }
            space.simulate();
            
            space.print(); // debug

        }

        // void loadSpace(const char* image_source){
        //     space.loadCircuit(image_source);
        // }

        void addSatellite(Circuit* circuit_ptr){ //todo: rename
            circuits.push_back(circuit_ptr);
        }

        LogicWire* getSpacePtr(){
            return &space;
        }

        void print(){
            cout << space.getInput(0)->checkPower() << " " << space.getOutput(0)->checkPower() << endl;
        }

        System() : space(){
            space.loadCircuit("logicwire/circuits/space.png");
        };
};  