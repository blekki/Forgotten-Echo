#pragma once
#include <stdlib.h>
#include <vector>

#include "logicwire.h"

using namespace std;

class Circuit
{
    private:
    public:
        vector<LogicWire> schemes;

    public:
        void simulate(){
            vector<vector<bool>> new_input_states;

            for (uint a = 0; a < schemes.size(); a++) { // check every scheme
                vector<bool> states;
                for (uint b = 0; b < schemes[a].getInputsCount(); b++) { // check every scheme inputs
                    // new_input_states[a].push_back(false);
                    states.push_back(false);
                    
                    // check every input connection
                    Input* input_ptr = schemes[a].getInput(b);
                    for (uint c = 0; c < input_ptr->getGlobalConnectionsCount(); c++) {
                        Output* output_ptr = input_ptr->getConnection(c);
                        if (output_ptr->checkPower()) {
                            // new_input_states[a][b] = true;
                            states.at(b) = true;
                            break;
                        }
                    }


                }
                new_input_states.push_back(states);
                schemes[a].simulate();
            }

            for (uint a = 0; a < schemes.size(); a++) { // check every scheme
                for (uint b = 0; b < schemes[a].getInputsCount(); b++) { // check every scheme inputs
                    Input* input_ptr = schemes[a].getInput(b);
                    input_ptr->setPower(new_input_states[a][b]);
                }
            }
        }

        // void connect(Input* input, Output* output){
        void connect(){ // todo: make it more useful
            schemes[2].getInput(0)->addGlobalConnection(schemes[0].getOutput(0));
            schemes[2].getInput(1)->addGlobalConnection(schemes[1].getOutput(1));
        }

        Circuit(){ // todo: update that
            LogicWire first;
            first.loadCircuit("logicwire/circuits/test-1.png");
            schemes.push_back(first);

            LogicWire second;
            second.loadCircuit("logicwire/circuits/test-2.png");
            schemes.push_back(second);

            LogicWire third;
            third.loadCircuit("logicwire/circuits/test-3.png");
            schemes.push_back(third);

            connect();
        }
};