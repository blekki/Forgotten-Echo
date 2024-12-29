#pragma once
#include "model.h"
#include <GLFW/glfw3.h>

#include "qued.h"
#include "matrices.h"
#include "structures/xyz.h"

class Object: public Model{
    public:
        // coordinates
        Vec3 position;

        // rotate position
        Matrix4 rotationPosition;

        float scale = 1.0f;

        void drawTriangles();

    public:
        Object(){
            // розділити кватерніон на 90 градусів
        };
        void setPosition(float x, float y, float z);
        void setRotate(float angleX);
        void setScale(float scale);
        
        void draw(){
            glPushMatrix();
            glTranslated(position.x, position.y, position.z);
            glScalef(scale, scale, scale);
            glMultMatrixf(rotationPosition.ptr());
            // glRotatef(angleX * glfwGetTime(), 0.0f, 1.0f, 0.0f); // rotate around itself
            drawTriangles();
            glPopMatrix();
        }

        // function for rotate object
        void addRotateMatrix(Matrix4 matrix){
            rotationPosition = multiplyMatrix(rotationPosition, matrix);
        }

        void addTranslateVec(Vec3 vec){
            Vec3 translateVec = multiplyMatrixVec(rotationPosition, vec);
            position.x += translateVec.x / 5.0f;
            position.y += translateVec.y / 5.0f;
            position.z += translateVec.z / 5.0f;
        }

        virtual ~Object(){};
};