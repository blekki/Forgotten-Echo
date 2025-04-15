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

    private:
        void applyOtherChanges();
        
    public:
        void powerControlPin();
        void simulate();
        
        void addComponent(Component* component);
        void connect(uint classInput_index,  uint input_index, 
                     uint classOutput_index, uint output_index);
        void connectToControlPin(uint classWithInput,  uint input_index);

        Circuit();
        ~Circuit();
};