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
        vector<Component*> priorityTree;
        // "priorityTree" saves sequence priority
        // FIRST element has a lower priority
        // SECOND - highter etc. The last one has the higtest priority
                                        

    public:
        void powerControlPin(); //todo:remove or change

        void simulate();
        void simulate2();
        void applyChanges();
        
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
            // clog << "deleted components: " << endl; //todo: change
            for (Component* elem : components) {
                delete elem;
                // clog << "#";
            }
            // clog << endl;
        }
};