#include "circuit.h"
#include "utility" // <-- todo: remove
#include <set>
#include "functional" 

// basic methods
// void Circuit::powerTheInput(uint scheme_id, uint input_id){
//     components[scheme_id]->powerTheInput(input_id, true);
// }

void Circuit::powerControlPin(){
    controlPin.setPower(true);
}

void Circuit::print(){
    // vector<LogicComponent*> components;
    // Component* - pointer on component (logic and special)

    // for (auto logic_it = logicComponents.begin(); logic_it != logicComponents.end(); logic_it++) {
    //     (logic_it)->print();
    // }
    // for (auto special_it = specialComponents.begin(); special_it != specialComponents.end(); special_it++) {
    //     (special_it)->print();
    // }
}

// other methods
void Circuit::simulate(){
    // (global connections)
    // for (uint a = 0; a < priorityTree.size(); a++) { // check every scheme
    for (int a = priorityTree.size() - 1; a >= 0; a--) { // check every scheme
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

void Circuit::generatePriorityTree(){
    // logicComponents;
    // vector<LogicComponent*> components; // pointers to all components (logic and special)
    // for (uint logic = 0; logic < logicComponents.size(); logic++)
    //     components.push_back(&logicComponents[logic]);
    // for (uint special = 0; special < specialComponents.size(); special++)
    //     components.push_back(&specialComponents[special]);

    // cout << "IMPORTANT:" << logicComponents.at(0).backRelationsCount() << endl;

    priorityTree.clear();
    set<Component*> visited; // save already visited component

    // back to front way
    for (auto it = components.begin(); it != components.end(); it++) {

        if ((*it)->backRelationsCount() != 0 ) // if this component isn't last, continue search
            continue;
        //todo: search all component with connection to the space
        

        function<void(vector<Component*>::iterator)> walker; // <-- search line relations
        walker = [&](auto component_it) {
            // if we visited this component before, stop loop iteration
            if (visited.find((*component_it)) == visited.end()) {
                visited.insert((*component_it)); // make this component visited
                priorityTree.push_back((*component_it)); // save new priority elem
            }
            else return;
            
            // check other connections of this component
            vector<Component*> *relations_ptr = (*component_it)->getFrontRelations();
            for (auto relation_it = relations_ptr->begin(); relation_it != relations_ptr->end(); relation_it++) {
                walker(relation_it);
            }

        };
        walker(it);
        
    }
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

// // Add various components
// void Circuit::addComponent(LogicComponent component){
//     logicComponents.push_back(component);
//     // components.push_back(&logicComponents.back());
// }

// void Circuit::addComponent(SpecialComponent component){
//     specialComponents.push_back(component);
//     // components.push_back(&specialComponents.back());
// }