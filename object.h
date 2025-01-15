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

        void drawTriangles();

    public:
        void setScale(float scale);
        Matrix4 makeModelMatrix();

        // virtual void draw(Brightness &brightnessShader){
        virtual void draw(){
            // brightnessShader.setModelMatrix(makeModelMatrix());
            drawTriangles();
        }

        Object(){
            scale = 1.0f;
            // розділити кватерніон на 90 градусів
        };

        virtual ~Object(){};
};