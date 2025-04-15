#include "circuit.h"
#include "utility" // <-- todo: remove
#include <set>
#include "functional" 

#include "component.h"

void Circuit::powerControlPin(){
    controlPin.setPower(true);
}

// other methods
void Circuit::simulate(){
    for (uint a = 0; a < priorityTree.size(); a++) { // check every scheme
                                                         // here we must check priorityTree started of last elem
        vector<bool> new_input_states;

        for (uint b = 0; b < priorityTree[a]->getInputsCount(); b++) { // check every scheme inputs
            new_input_states.push_back(false);
            
            // check every input connections
            Input* input_ptr = priorityTree[a]->getInput(b);
            for (uint c = 0; c < input_ptr->getGlobalConnectionsCount(); c++) { // check every connection to the input

                Output* output_ptr = input_ptr->getConnection(c);
                if (output_ptr->checkPower()) {
                    new_input_states.at(b) = true;
                    break;
                }
            }

            input_ptr->setPower(new_input_states.at(b));
        }
        priorityTree[a]->simulate(); // simulation inside scheme
    }
}

void Circuit::simulate2(){
    for (uint a = 0; a < components.size(); a++) { // check every scheme

        vector<bool> new_input_states;
        
        for (uint b = 0; b < components[a]->getInputsCount(); b++) { // check every scheme inputs
            components[a]->pushNextInputState(b, false);
            // new_input_states.push_back(false);
            
            // check every input connections
            Input* input_ptr = components[a]->getInput(b);
            for (uint c = 0; c < input_ptr->getGlobalConnectionsCount(); c++) { // check every connection to the input

                Output* output_ptr = input_ptr->getConnection(c);
                if (output_ptr->checkPower()) {
                    components[a]->pushNextInputState(b, true);
                    // new_input_states.at(b) = true;
                    break;
                }
            }
            // input_ptr->setPower(new_input_states.at(b));
            components[a]->applyNextInputState(b);
            // components[a]->applyNextInputState(b);
        }
        // components[a]->applyNextInputState();
        components[a]->simulate(); // simulation inside scheme
    }
}

void Circuit::applyChanges(){
    for (uint a = 0; a < components.size(); a++) {
        components[a]->applyWireChanges();
        components[a]->applyOutputChanges();
    }
}

void Circuit::generatePriorityTree(){

    priorityTree.clear();
    vector<Component*> start_components;
    
    set<Component*> visited; // save already visited component

    // back to front way
    for (auto component_it = components.begin(); component_it != components.end(); ++component_it) {
        cout << "avalible components: " << (*component_it) << endl;
        if ((*component_it)->backRelationsCount() > 0) { // if this component isn't last (with back relation), continue search
            if ((*component_it)->frontRelationsCount() == 0) {
                visited.insert(*component_it);
                start_components.push_back(*component_it);
            }
            continue;
        }

        set<Component*> new_visited;
        
        function<void(vector<Component*>::iterator)> front_walker; // search front relations
        front_walker = [&](auto component_it){
            if (new_visited.find((*component_it)) == new_visited.end()) // if didn't visit last iteration this component
                if (visited.find((*component_it)) == visited.end()) { // check is this component already visited with current way 
                    
                    visited.insert((*component_it));
                    new_visited.insert((*component_it));

                    vector<Component*> *relations = (*component_it)->getFrontRelations();
                    if (relations->size() == 0) {
                        start_components.push_back(*component_it);
                        return;
                    }
                    
                    for (auto relation_it = relations->begin(); relation_it != relations->end(); ++relation_it) {
                        front_walker(relation_it);
                    }
                }
                else return;
            else start_components.push_back((*component_it));
        };
        front_walker(component_it);
        new_visited.clear();

    }

    visited.clear();
    for (auto component_it = start_components.begin(); component_it != start_components.end(); ++component_it) {
        function<void(vector<Component*>::iterator)> back_walker; // search back relations
        back_walker = [&](auto component_it) {
            // if we visited this component before, stop lambda function
            if (visited.find((*component_it)) == visited.end()) {
                visited.insert((*component_it));
                priorityTree.push_back((*component_it));
                
                vector<Component*> *relations_ptr = (*component_it)->getBackRelations();
                for (auto relation_it = relations_ptr->begin(); relation_it != relations_ptr->end(); ++relation_it) {
                    back_walker(relation_it);
                }
            }
            else return;
        };
        back_walker(component_it);
    }
    
    // debug
    cout << endl;
    for (uint i = 0; i < components.size(); i++) {
        cout << "+ " << components.at(i) << endl;
    }
    cout << endl;
    for (uint i = 0; i < priorityTree.size(); i++) {
        cout << "- " << priorityTree.at(i) << endl;
    }
    cout << endl;
    for (uint i = 0; i < start_components.size(); i++) {
        cout << "first comp: " << start_components.at(i) << endl;
    }
    cout << endl;
}

void Circuit::connect(uint classWithInput,  uint input_index, //todo: remake
                      uint classWithOutput, uint output_index){
    // add input connection
    Input* input   = components[classWithInput]->getInput(input_index);
    Output* output = components[classWithOutput]->getOutput(output_index);
    input->addGlobalConnection(output);
    
    // add components relations
    components[classWithInput]->addFrontRelation(components[classWithOutput]);
    components[classWithOutput]->addBackRelation(components[classWithInput]);
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
    
//     // add components relations
//     classWithInput->addFrontRelation(classWithOutput);
//     classWithOutput->addBackRelation(classWithInput);
// }

// void Circuit::connectToControlPin(LogicComponent* classWithInput,  uint input_index){
//     // add input connection
//     Input* input = classWithInput->getInput(input_index);
//     input->addGlobalConnection(&controlPin);
// }