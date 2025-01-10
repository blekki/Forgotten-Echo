#pragma once
#include <math.h>
#include "model.h"
#include <GLFW/glfw3.h>

#include "matrices.h"
#include "structures/xyz.h"

class Object: public Model{
    private:
        string name;
        xyz_t position;
        Matrix4 rotate;
        float scale = 1.0f;

        void drawTriangles();
        Matrix4 makeModelMatrix();
        void prepareRotate(float rotX, float rotY, float rotZ);

    public:
        void setPosition(float x, float y, float z);
        void setRotate(float angleX);
        void setScale(float scale);
        float getX();
        float getY();
        float getZ();
        xyz_t getXYZ();
        Matrix4 getRotate();
        
        virtual void draw(){
            // glRotatef(angleX * glfwGetTime(), 0.0f, 1.0f, 0.0f); // rotate around itself
            drawTriangles();
        }

        // function for rotate object
        void addRotateMatrix(Matrix4 matrix){
            rotate = multiplyMatrix(rotate, matrix);
        }

        void addTranslateVec(Vec3 vec){
            Vec3 translateVec = multiplyMatrixVec(rotate, vec);
            position.x += translateVec.x / 5.0f;
            position.y += translateVec.y / 5.0f;
            position.z += translateVec.z / 5.0f;
        }

        Matrix4 getModelMatrix(){
            return makeModelMatrix();
        }

        void preparation(float rotX, float rotY, float rotZ){
            prepareRotate(rotX, rotY, rotZ);
        }

        Object(){
            // розділити кватерніон на 90 градусів
        };

        virtual ~Object(){};
};