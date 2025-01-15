#pragma once

#include "shader/brightness.h"

#include "object.h"

class Spaceship: public Object
{
    public:
        virtual void draw(Brightness &brightnessShader){
            brightnessShader.setModelMatrix(makeModelMatrix());
            Object::draw();
        }

        Spaceship(){};
};