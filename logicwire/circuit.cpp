#include "circuit.h"

// basic methods
void Circuit::powerTheInput(uint scheme_id, uint input_id){
    schemes[scheme_id].powerTheInput(input_id, true);
}

void Circuit::print(uint scheme_id){
    schemes[scheme_id].print();
}

void Circuit::print(){
    for (uint i = 0; i < schemes.size(); i++)
        schemes[i].print();
}

// other methods
void Circuit::simulate(){
    // vector<vector<bool>> new_input_states;

    for (uint a = 0; a < schemes.size(); a++) { // check every scheme
        vector<bool> new_input_states;

        for (uint b = 0; b < schemes[a].getInputsCount(); b++) { // check every scheme inputs
            new_input_states.push_back(false);
            
            // check every input connections
            Input* current_input_ptr = schemes[a].getInput(b);
            for (uint c = 0; c < current_input_ptr->getGlobalConnectionsCount(); c++) { // check every connection to the input

                Output* current_output_ptr = current_input_ptr->getConnection(c);
                if (current_output_ptr->checkPower()) {
                    new_input_states.at(b) = true;
                    break;
                }
            }

            current_input_ptr->setPower(new_input_states.at(b));
        }
        // new_input_states.push_back(states);
        schemes[a].simulate();
    }

    controlPin.setPower(false);
    
    // use new states
    // for (uint a = 0; a < schemes.size(); a++) { // check every scheme
    //     schemes[a].simulate();
    //     for (uint b = 0; b < schemes[a].getInputsCount(); b++) { // check every scheme inputs
    //         Input* input_ptr = schemes[a].getInput(b);
    //         input_ptr->setPower(new_input_states[a][b]);

    //         cout << new_input_states[a][b] << " ";
    //     }
    // }
    // cout << endl;
}

// void connect(Input* input, Output* output){
void Circuit::connect(){ // todo: make it more useful
    schemes[0].getInput(0)->addGlobalConnection(&controlPin);
    
    schemes[1].getInput(0)->addGlobalConnection(schemes[0].getOutput(0));
    schemes[2].getInput(0)->addGlobalConnection(schemes[1].getOutput(0));
    // schemes[0].getInput(0)->addGlobalConnection(schemes[2].getOutput(0));
}

Circuit::Circuit(){ // todo: update that
    Component first("logicwire/circuits/repeater.png");
    schemes.push_back(first);

    Component second("logicwire/circuits/test-4.png");
    schemes.push_back(second);

    Component third("logicwire/circuits/test-4.png");
    schemes.push_back(third);

    connect();
}