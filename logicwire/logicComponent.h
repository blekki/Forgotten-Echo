#pragma once
#include "component.h"
#include "logicwire.h"

class LogicComponent: public LogicWire
{
    private:
        string name;
        uint width;
        uint height;
        uint consuming;

        vector<LogicComponent*> front_relations; // save relations as input makes, but with the classes
        vector<LogicComponent*> back_relations;

    public:
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

        // input/output depend functions
        virtual uint getInputsCount(){
            return inputs.size();
        }
        virtual Input* getInput(uint id){
            return &inputs.at(id);
        }
        virtual uint getOutputsCount(){
            return outputs.size();
        }
        virtual Output* getOutput(uint id){
            return &outputs.at(id);
        }

        // everything for relations
        virtual void addFrontRelation(LogicComponent* component_ptr){
            front_relations.push_back(component_ptr);
        }
        virtual void addBackRelation(LogicComponent* component_ptr){
            back_relations.push_back(component_ptr);
        }
        virtual vector<LogicComponent*>* getFrontRelations(){
            return &front_relations;
        }
        virtual vector<LogicComponent*>* getBackRelations(){
            return &back_relations;
        }
        virtual uint frontRelationsCount(){
            return front_relations.size();
        }
        virtual uint backRelationsCount(){
            return back_relations.size();
        }

        // constructor
        LogicComponent(const char* image_source)
        : LogicWire(image_source)
        {};
};