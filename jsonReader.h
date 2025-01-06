#pragma once

#include "planet.h"
#include "object.h"

class JsonReader{
    private:
        void readJsonPlanet(Planet *planet, string path);
        void readJsonSpaceship(Object *object, string path);

    public:
        void getPlanet(Planet *planet, string path){
            readJsonPlanet(planet, path);
        }
        
        void getSpaceship(Object *object, string path){
            readJsonSpaceship(object, path);
        }

        void testReader(Object *object, string path);
};