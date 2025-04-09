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

        vector<Component*> components; //save components
        vector<Component*> priorityTree; // remember sequence priority

        //todo: rotate priorityTree be 180 degrees

    public:
        void powerTheInput(uint scheme_id, uint input_id); //todo: remove
        void powerControlPin(); //todo:remove or change

        void print(uint scheme_id);
        void print();

        void simulate();
        
        // void addComponent(LogicComponent component);
        // void addComponent(SpecialComponent component);
        // void connectToControlPin(LogicComponent* classWithInput,  uint input_index);
        void addComponent(Component* component){
            components.push_back(component);
        }
        
        void connect(uint classInput_index,  uint input_index, 
                     uint classOutput_index, uint output_index);
        void connectToControlPin(uint classWithInput,  uint input_index);

        void generatePriorityTree();

        Circuit(){
            controlPin.setPower(true); // controlPin is TRUE everytime
        };

        ~Circuit(){
            clog << "deleted components: " << endl;
            for (Component* elem : components) {
                delete elem;
                clog << "#";
            }
            clog << endl;
        }
};