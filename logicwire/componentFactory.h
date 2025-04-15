#pragma once
#include "component.h"
#include "logicComponent.h"
#include "specialComponent.h"


class ComponentFactory
{
    public:
        // logic components
        Component* createTube();
        Component* createRepeater();
        Component* createGate();
        Component* createAND();
        Component* createNAND();
        // special components
        Component* createAntenna();
};