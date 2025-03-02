#pragma once

#include "planet.h"
#include "object.h"
#include "sun.h"
#include "spaceship.h"
#include "logicwire/component.h"

class JsonReader{
    public:
        void readJsonPlanet(Planet *planet, string path);
        void readJsonSun(Sun *sun, string path);
        void readJsonSpaceship(Spaceship *object, string path);
        void readJsonCircuit(Component *component, string path);
};