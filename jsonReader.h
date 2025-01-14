#pragma once

#include "planet.h"
#include "object.h"
#include "sun.h"

class JsonReader{
    public:
        void readJsonPlanet(Planet *planet, string path);
        void readJsonSun(Sun *sun, string path);
        void readJsonSpaceship(Object *object, string path);
};