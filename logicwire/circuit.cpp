#include "circuit.h"

// basic methods
void Circuit::powerTheInput(uint scheme_id, uint input_id){
    components[scheme_id]->powerTheInput(input_id, true);
}

void Circuit::powerControlPin(){
    controlPin.setPower(true);
}

void Circuit::print(uint scheme_id){
    components[scheme_id]->print();
}

void Circuit::print(){
    for (auto it = components.begin(); it != components.end(); it++)
       (*it)->print();
}

// other methods
void Circuit::simulate(){

    // (global connections)
    for (uint a = 0; a < components.size(); a++) { // check every scheme
        vector<bool> new_input_states;

        for (uint b = 0; b < components[a]->getInputsCount(); b++) { // check every scheme inputs
            new_input_states.push_back(false);
            
            // check every input connections
            Input* current_input_ptr = components[a]->getInput(b);
            for (uint c = 0; c < current_input_ptr->getGlobalConnectionsCount(); c++) { // check every connection to the input

                Output* current_output_ptr = current_input_ptr->getConnection(c);
                if (current_output_ptr->checkPower()) {
                    new_input_states.at(b) = true;
                    break;
                }
            }

            current_input_ptr->setPower(new_input_states.at(b));
        }
        components[a]->simulate(); // simulation inside scheme
    }

    controlPin.setPower(false);
}

// void connect(Input* input, Output* output){
//     input->addGlobalConnection(output);
// }

// void Circuit::connect(){ // todo: make it more useful
//     schemes[0].getInput(0)->addGlobalConnection(&controlPin);
//     schemes[1].getInput(0)->addGlobalConnection(schemes[0].getOutput(0));
//     schemes[2].getInput(0)->addGlobalConnection(schemes[1].getOutput(0));
//     // schemes[0].getInput(0)->addGlobalConnection(schemes[2].getOutput(0));

//     space_ptr->getInput(0)->addGlobalConnection(schemes[2].getOutput(0));
// }

// Circuit::Circuit(){ // todo: update that
//     Component first("logicwire/circuits/repeater.png");
//     schemes.push_back(first);

//     Component second("logicwire/circuits/test-4.png");
//     schemes.push_back(second);

//     Component third("logicwire/circuits/antenna.png");
//     schemes.push_back(third);

//     // connect();
// }