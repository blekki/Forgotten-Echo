#pragma once
#include "model.h"
#include <GLFW/glfw3.h>
#include "qued.h"

class Object: public Model{
    private:
        //coordinates
        Vec3 position;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        //rotate position
        Matrix4 rotation;
        Matrix4 cwYaw;
        Matrix4 ccwYaw;

        float scale = 1.0f;

        void drawTriangles();

    public:
        Object(){ 
            Vec3 vecUp {0, 1, 0};
            Vec3 vecRight {1, 0, 0};
            Qued rot(vecUp, vecRight);
            Qued rot2(vecUp, vecRight);
            //розділити кватерніон на 90 градусів
            cwYaw = rotationMatrix(rot);
            rot2.conjugate();
            ccwYaw = rotationMatrix(rot2);
            yaw(false);
        };
        void setPosition(float x, float y, float z);
        void setRotate(float angleX);
        void setScale(float scale);
        
        void draw(){
            glPushMatrix();
            glTranslated(x, y, z);
            glScalef(scale, scale, scale);
            glMultMatrixf(rotation.ptr());
            // glRotatef(angleX * glfwGetTime(), 0.0f, 1.0f, 0.0f); // rotate around itself
            drawTriangles();
            glPopMatrix();
        }

        void yaw(bool cw){
            rotation = multiplyMatrix(rotation, (cw ? cwYaw : ccwYaw));
        }

        virtual ~Object(){};
};