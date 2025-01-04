#pragma once

#include "planet.h"
#include "object.h"

class JsonReader{
    private:
        void readJsonPlanet(Planet *planet, string path);
        void readJsonSpaceship(Object *spaceship, string path);

    public:
        void getPlanet(Planet *planet, string path){
            readJsonPlanet(planet, path);
        }
        
        void getSpaceship(Object *spaceship, string path){
            readJsonSpaceship(spaceship, path);
        }
};