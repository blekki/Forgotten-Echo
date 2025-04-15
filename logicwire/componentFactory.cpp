#include "componentFactory.h"

// logic components
Component* ComponentFactory::createTube(){
    return new LogicComponent("logicwire/circuits/tube.png");
}

Component* ComponentFactory::createRepeater(){
    return new LogicComponent("logicwire/circuits/repeater.png");
}

Component* ComponentFactory::createGate(){
    return new LogicComponent("logicwire/circuits/gate.png");
}

Component* ComponentFactory::createAND(){
    return new LogicComponent("logicwire/circuits/AND.png");
}

Component* ComponentFactory::createNAND(){
    return new LogicComponent("logicwire/circuits/NAND.png");
}

// special components
Component* ComponentFactory::createAntenna(){
    return new SpecialComponent("logicwire/circuits/antenna.png");
}