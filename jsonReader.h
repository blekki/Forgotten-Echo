#pragma once

#include "planet.h"
#include "object.h"
#include "sun.h"
#include "spaceship.h"
#include "logicwire/component.h"
#include "logicwire/circuit.h"

class JsonReader{
    public:
        void readJsonPlanet(Planet *planet, string path);
        void readJsonSun(Sun *sun, string path);
        void readJsonSpaceship(Spaceship *object, string path);
        void readJsonComponent(Component *component, string path);
        void readJsonCircuit(Component *Circuit, string path);
};