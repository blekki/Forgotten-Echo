#pragma once
#include "component.h"
#include "logicComponent.h"
#include "specialComponent.h"


class ComponentFactory
{
    public:
        Component* createRepeater(){
            return new LogicComponent("logicwire/circuits/repeater.png");
        }
        
        Component* createGate(){
            return new LogicComponent("logicwire/circuits/gate.png");
        }
        
        Component* createAntenna(){
            return new SpecialComponent("logicwire/circuits/antenna.png");
        }
};