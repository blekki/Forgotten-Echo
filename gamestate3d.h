#pragma once

#include "shader/brightness.h"
#include "shader/planetShader.h"
#include "shader/sunShader.h"

#include "zerostate.h"

class Gamestate3d : public Zerostate
{
    protected:
        // shader preparation
        Brightness brightnessShader;
        PlanetShader planetShader;
        SunShader sunShader;

    public:
        virtual void prepareMatrix();

        Gamestate3d(){};
};