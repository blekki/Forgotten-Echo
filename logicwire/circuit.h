#pragma once
#include <stdlib.h>
#include <vector>

#include "component.h"
#include "logicComponent.h"
#include "specialComponent.h"

using namespace std;

class Circuit
{
    private:
        Output controlPin;

        vector<LogicComponent> logicComponents;
        vector<SpecialComponent> specialComponents;

        // LogicWire* space_ptr; //todo: replace to the Antenna class

        // vector<Component*> components; // pointer to all components (logic and special)
        vector<LogicComponent*> priorityTree; // remember sequence priority

        //todo: rotate priorityTree be 180 degrees

    public:
        void powerTheInput(uint scheme_id, uint input_id); //todo: remove
        void powerControlPin(); //todo:remove or change

        void print(uint scheme_id);
        void print();

        void simulate();

        // void addSpacePtr(LogicWire* space_ptr){
        //     this->space_ptr = space_ptr;
        // }

        // Output* getControlPin(){
        //     return &controlPin;
        // }
        
        void addComponent(LogicComponent component);
        void addComponent(SpecialComponent component);
        
        void connect(LogicComponent* classWithInput,  uint input_index, 
                     LogicComponent* classWithOutput, uint output_index);
        void connectToControlPin(LogicComponent* classWithInput,  uint input_index);

        void generatePriorityTree();

        Circuit(){
            controlPin.setPower(true); // controlPin must be TRUE everytime
        };
};