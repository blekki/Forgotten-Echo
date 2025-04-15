#pragma once
#include <vector>

#include "logicwire.h"

using namespace std;

class Component: public LogicWire
{
    protected:
        string name;
        uint width;
        uint height;
        uint consuming;

    public:
        virtual void simulate() = 0;

        void setName(string name){
            this->name = name;
        }
        void setSize(uint width, uint height){
            this->width = width;
            this->height = height;
        }
        void setConsuming(uint comsuming){
            this->consuming = consuming;    
        }

        // depend on input/output functions
        uint getInputsCount(){
            return inputs.size();
        }
        Input* getInput(uint id){
            return &inputs.at(id);
        }
        uint getOutputsCount(){
            return outputs.size();
        }
        Output* getOutput(uint id){
            return &outputs.at(id);
        }

        Component(const char* image_source)
        : LogicWire(image_source)
        {}
};