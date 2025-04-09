#pragma once
#include "component.h"

class SpecialComponent: public Component
{
    public:
        virtual void simulate() override { //todo: update
            LogicWire::simulate();
            clog << "Antenna output: " << outputs.at(0).checkPower() << endl;
        }

        SpecialComponent(const char* image_source)
        : Component(image_source)
        {}
};