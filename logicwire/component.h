#pragma once

#include "logicwire.h"

class Component
{
    public:
        virtual uint getInputsCount() = 0;
        virtual Input* getInput(uint id) = 0;

        virtual uint getOutputsCount() = 0;
        virtual Output* getOutput(uint id) = 0;


        virtual void addFrontRelation(Component* component_ptr) = 0;
        virtual void addBackRelation(Component* component_ptr) = 0;
        virtual vector<Component*>* getRelations() = 0;
        virtual uint relationsCount() = 0;
};