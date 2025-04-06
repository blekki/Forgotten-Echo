#pragma once

#include "logicwire.h"

class Component: public LogicWire
{
    private:
        string name;

        uint width;
        uint height;
        uint consuming;

        vector<Component*> relations; // save relations as input makes, but with the classes

    public:
        void setName(string name);
        void setSize(uint width, uint height);
        void setConsuming(uint comsuming);

        Component(const char* image_source)
        :   LogicWire(image_source)
        {};

        void addRelation(Component* component_ptr){
            relations.push_back(component_ptr);
            cout << "relations " << relations.at(0) << endl; // debug
        }

        // Component* getRelation(uint index){
        //     return relations.at(index);
        // }

        vector<Component*>* getRelations(){
            return &relations;
        }

        uint relationsCount(){
            return relations.size();
        }


        // new
        // virtual uint getInputsCount() = 0;
        // virtual Input* getInput(uint id) = 0;
        // virtual Output* getOutput(uint id) = 0;
        // getSpaceInput()

        uint getInputsCount(){
            return inputs.size();
        }
        uint getOutputsCount(){
            return outputs.size();
        }
        Input* getInput(uint id){
            return &inputs.at(id);
        }
        Output* getOutput(uint id){
            return &outputs.at(id);
        }
};