#pragma once
#include <stdlib.h>
#include <vector>

#include "component.h"

using namespace std;

class Circuit
{
    private:
        Output controlPin;
        vector<Component> schemes;

        LogicWire* space_ptr;

    public:
        void powerTheInput(uint scheme_id, uint input_id);
        void powerControlPin();

        void print(uint scheme_id);
        void print();

        void simulate();

        void addSpacePtr(LogicWire* space_ptr){
            this->space_ptr = space_ptr;
        }

        // void connect(Input* input, Output* output){
        void connect();
        void connectAntenna();

        Circuit();
};