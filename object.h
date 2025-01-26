#pragma once
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "matrices.h"
#include "structures/xyz.h"

#include "model.h"
#include "entity.h"

class Object: public Model, public Entity
{
    protected:
        float scale;

    public:
        void setScale(float scale);
        virtual Matrix4 makeModelMatrix();

        virtual void draw();

        Object(){
            scale = 1.0f;
        };

        virtual ~Object(){};
};