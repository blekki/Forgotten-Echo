#pragma once

#include "planet.h"
#include "object.h"
#include "sun.h"
#include "spaceship.h"
#include "logicwire/logicComponent.h"
#include "logicwire/circuit.h"

class JsonReader{
    public:
        void readJsonPlanet(Planet *planet, string path);
        void readJsonSun(Sun *sun, string path);
        void readJsonSpaceship(Spaceship *object, string path);
        void readJsonComponent(LogicComponent *component, string path);
        void readJsonCircuit(LogicComponent *Circuit, string path);
};