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
    vector<Component*> components;
    // Component* - pointer on component (logic and special)

    for (auto logic_it = logicComponents.begin(); logic_it != logicComponents.end(); logic_it++) {
        (logic_it)->print();
    }
    for (auto special_it = specialComponents.begin(); special_it != specialComponents.end(); special_it++) {
        (special_it)->print();
    }
}

// other methods
void Circuit::simulate(){
    controlPin.setPower(true);
    // (global connections)
    for (uint a = 0; a < priorityTree.size(); a++) { // check every scheme
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

    // controlPin.setPower(false);
}

void Circuit::generatePriorityTree(){
    // vector<pair<Component*, bool>> components;
    // vector<Component*> components;
    // Component* - pointer on component (logic and special)

    // for (uint a = 0; a < specialComponents.size(); a++) {
    //     components.push_back(&specialComponents.at(a));
    // }
    // for (uint a = 0; a < logicComponents.size(); a++) {
    //     components.push_back(&logicComponents.at(a));
    // }

    priorityTree.clear();

    for (auto it = components.begin(); it != components.end(); it++) {

        if ((*it)->relationsCount() != 0 ) // if it has back relations continue search
            continue;
        
        // search all front relations
        function<void(vector<Component*>::iterator)> walker; // <-- search line relations

        set<Component*> visited; // save already visited components
        walker = [&](auto component_it) {
            // if we visited this component before, stop function
            if (visited.find((*component_it)) == visited.end())
                return;
            // else make this component visited
            visited.insert((*component_it));
            priorityTree.push_back((*component_it)); // save new elem priority
            
            #define relations (*component_it)->getRelations()
            for (auto relation_it = relations->begin(); relation_it != relations->end(); relation_it++) {
                walker(relation_it);
            }

        };
        walker(it);
        
    }
}

void Circuit::connect(Component* classWithInput,  uint input_index, 
                      Component* classWithOutput, uint output_index){
    
    // input connection
    #define input classWithInput->getInput(input_index)
    #define output classWithOutput->getOutput(output_index)
    input->addGlobalConnection(output);
    
    // add components relation
    classWithInput->addRelation(classWithOutput);
}

void Circuit::connectToControlPin(Component* classWithInput,  uint input_index){

    // input connection
    #define input classWithInput->getInput(input_index)
    input->addGlobalConnection(&controlPin);
}

// add various components
void Circuit::addComponent(LogicComponent component){
    logicComponents.push_back(component);
    components.push_back(&logicComponents.back());

    // debug
    // LogicComponent* ptr = &logicComponents.back();
    // cout << ptr << endl;
}

void Circuit::addComponent(SpecialComponent component){
    specialComponents.push_back(component);
    components.push_back(&specialComponents.back());
    
    // debug
    // SpecialComponent* ptr = &specialComponents.back();
    // cout << ptr << endl;
}