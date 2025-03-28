#pragma once
#include <stdlib.h>
#include <vector>

#include "component.h"
#include "logic_component.h"
#include "special_component.h"

using namespace std;

class Circuit
{
    private:
        Output controlPin = true;

        vector<LogicComponent> logicComponents;
        vector<SpecialComponent> specialComponents;

        LogicWire* space_ptr; //todo: replace to the Antenna class

        vector<Component*> components; // pointer to all components (logic and special)
        vector<Component*> priorityTree; // remember sequence priority

    public:
        void powerTheInput(uint scheme_id, uint input_id);
        void powerControlPin();

        void print(uint scheme_id);
        void print();

        void simulate();

        void addSpacePtr(LogicWire* space_ptr){
            this->space_ptr = space_ptr;
        }


        // test
    
        Input* getInput(uint component_id, uint input_id){
            return components[component_id]->getInput(input_id);
        }

        Output* getOutput(uint component_id, uint output_id){
            return components[component_id]->getOutput(output_id);
        }

        Output* getControlPin(){
            return &controlPin;
        }
        
        
        void addComponent(LogicComponent component);
        void addComponent(SpecialComponent component);

        void connect(Component* classWithInput,  uint input_index, 
                     Component* classWithOutput, uint output_index);
        
        void connectToControlPin(Component* classWithInput,  uint input_index);

        void generatePriorityTree();

        Circuit(){};
};