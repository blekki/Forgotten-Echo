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

    public:
        void powerTheInput(uint scheme_id, uint input_id);
        void powerControl(){
            controlPin.setPower(true);
        }

        void print(uint scheme_id);
        void print();

        void simulate();

        // void connect(Input* input, Output* output){
        void connect();

        Circuit();
};