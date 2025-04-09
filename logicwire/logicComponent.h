#pragma once
#include "component.h"
#include "logicwire.h"

class LogicComponent: public Component
{
    public:
        virtual void simulate() override {
            LogicWire::simulate();
        }
        
        LogicComponent(const char* image_source)
        : Component(image_source)
        {};
};