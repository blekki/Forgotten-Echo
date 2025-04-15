#include "circuit.h"
#include "utility" // <-- todo: remove
#include <set>
#include "functional" 

#include "component.h"

void Circuit::powerControlPin(){
    controlPin.setPower(true);
}

void Circuit::applyOtherChanges(){
    for (uint a = 0; a < components.size(); a++) {
        components[a]->applyWireChanges();
        components[a]->applyOutputChanges();
    }
}

void Circuit::simulate(){
    for (uint a = 0; a < components.size(); a++) { // check every scheme

        for (uint b = 0; b < components[a]->getInputsCount(); b++) { // check every scheme inputs
            components[a]->saveNewInputState(b, false);
            
            // check every input connections
            Input* input_ptr = components[a]->getInput(b);
            for (uint c = 0; c < input_ptr->getGlobalConnectionsCount(); c++) { // check every connection to the input

                Output* output_ptr = input_ptr->getConnection(c);
                if (output_ptr->checkPower()) {
                    components[a]->saveNewInputState(b, true);
                    break;
                }
            }
            components[a]->applyInputChanges(b);
        }
        components[a]->simulate(); // simulation every wire inside components
    }
    applyOtherChanges();
}

void Circuit::addComponent(Component* component){
    components.push_back(component);
}

void Circuit::connect(uint classWithInput,  uint input_index, //todo: remake
                      uint classWithOutput, uint output_index){
    // add input connection
    Input* input   = components[classWithInput]->getInput(input_index);
    Output* output = components[classWithOutput]->getOutput(output_index);
    input->addGlobalConnection(output);
}

void Circuit::connectToControlPin(uint classWithInput,  uint input_index){ //todo: remake
    Input* input = components[classWithInput]->getInput(input_index);
    input->addGlobalConnection(&controlPin);
}

// void Circuit::connect(LogicComponent* classWithInput,  uint input_index, 
//                       LogicComponent* classWithOutput, uint output_index){
//     // add input connection
//     Input* input   = classWithInput->getInput(input_index);
//     Output* output = classWithOutput->getOutput(output_index);
//     input->addGlobalConnection(output);
// }

// void Circuit::connectToControlPin(LogicComponent* classWithInput,  uint input_index){
//     // add input connection
//     Input* input = classWithInput->getInput(input_index);
//     input->addGlobalConnection(&controlPin);
// }

Circuit::Circuit(){
    controlPin.setPower(true); // controlPin is TRUE everytime
};

Circuit::~Circuit(){
    for (Component* elem : components) {
        delete elem;
    }
}