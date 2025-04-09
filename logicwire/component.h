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

        vector<Component*> front_relations; // save relations as input makes, but with the classes
        vector<Component*> back_relations;
        
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
        // virtual uint getInputsCount() = 0;
        // virtual Input* getInput(uint id) = 0;

        // virtual uint getOutputsCount() = 0;
        // virtual Output* getOutput(uint id) = 0;

        // input/output depend functions
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

        // everything for relations
        void addFrontRelation(Component* component_ptr){
            front_relations.push_back(component_ptr);
        }
        void addBackRelation(Component* component_ptr){
            back_relations.push_back(component_ptr);
        }
        vector<Component*>* getFrontRelations(){
            return &front_relations;
        }
        vector<Component*>* getBackRelations(){
            return &back_relations;
        }
        uint frontRelationsCount(){
            return front_relations.size();
        }
        uint backRelationsCount(){
            return back_relations.size();
        }

        Component(const char* image_source)
        : LogicWire(image_source){}
};