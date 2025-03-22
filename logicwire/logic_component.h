#pragma once
#include "component.h"

class LogicComponent: public Component
{
    private:
        

    public:
        uint getInputsCount(){
            return inputs.size();
        }
        Input* getInput(uint id){
            return &inputs.at(id);
        }
        Output* getOutput(uint id){
            return &outputs.at(id);
        }

        LogicComponent(const char* image_source)
        : Component(image_source)
        {};
};