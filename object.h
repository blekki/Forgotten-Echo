#pragma once
#include "model.h"
#include <GLFW/glfw3.h>

class Object: public Model{
    private:
        //coordinates
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        //rotate position
        float angleX = 0.0f;

        float scale = 1.0f;

        void drawTriangles();

    public:
        void setPosition(float x, float y, float z);
        void setRotate(float angleX);
        void setScale(float scale);
        
        void draw(){
            glPushMatrix();
            glTranslated(x, y, z);
            glScalef(scale, scale, scale);
            glRotatef(angleX * glfwGetTime(), 0.0f, 1.0f, 0.0f); // rotate around itself
            drawTriangles();
            glPopMatrix();
        }

        Object(){};
        virtual ~Object(){};
};