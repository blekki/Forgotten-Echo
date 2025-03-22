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
        Output controlPin;
        vector<Component*> components;

        vector<LogicComponent> logicComponents;
        vector<SpecialComponent> specialComponents;

        LogicWire* space_ptr; //todo: replace to the Antenna class

    public:
        void powerTheInput(uint scheme_id, uint input_id);
        void powerControlPin();

        void print(uint scheme_id);
        void print();

        void simulate();

        void addSpacePtr(LogicWire* space_ptr){
            this->space_ptr = space_ptr;
        }
        
        // tests
        void connect(Input* input, Output* output){
            input->addGlobalConnection(output);
        }
        Input* getInput(uint component_id, uint input_id){
            return components[component_id]->getInput(input_id);
        }
        Output* getOutput(uint component_id, uint output_id){
            return components[component_id]->getOutput(output_id);
        }
        Output* getControlPin(){
            return &controlPin;
        }
        
        void addComponent(LogicComponent component){
            logicComponents.push_back(component);
            components.push_back(&logicComponents.back());

            // debug
            LogicComponent* ptr = &logicComponents.back();
            cout << ptr << endl;
        }
        void addComponent(SpecialComponent component){
            specialComponents.push_back(component);
            components.push_back(&specialComponents.back());
            
            // debug
            SpecialComponent* ptr = &specialComponents.back();
            cout << ptr << endl;
        }

        // void connect(Input* input, Output* output){
        // void connect();
        // void connectAntenna();

        Circuit(){};
};