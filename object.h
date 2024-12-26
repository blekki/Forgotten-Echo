#pragma once
#include "model.h"
#include <GLFW/glfw3.h>

#include "qued.h"
#include "matrices.h"

class Object: public Model{
    public:
        // coordinates
        Vec3 position;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // rotate position
        Matrix4 rotationPosition;
        
        // Matrix4 cwRoll;
        // Matrix4 ccwRoll;
        // Matrix4 cwYaw;
        // Matrix4 upPitch;

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
            glTranslated(x, y, z);
            glScalef(scale, scale, scale);
            // glLoadIdentity();
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
            x += translateVec.x / 5.0f;
            y += translateVec.y / 5.0f;
            z += translateVec.z / 5.0f;
        }

        virtual ~Object(){};
};