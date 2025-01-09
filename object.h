#pragma once
#include <math.h>
#include "model.h"
#include <GLFW/glfw3.h>

#include "qued.h"
#include "matrices.h"
#include "structures/xyz.h"
#include "structures/vec3.h"

class Object: public Model{
    public:
        string name;
        xyz_t position;
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
            // glTranslated(position.x, position.y, position.z);
            // glScalef(scale, scale, scale);
            // glMultMatrixf(rotationPosition.ptr());

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

        Matrix4 makeModelMatrix(){
            Matrix4 matrix;
            glPushMatrix();
            glLoadIdentity();
            glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
            glTranslated(position.x, position.y, position.z);
            glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
            glScalef(scale, scale, scale);
            glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
            // glMultMatrixf(rotationPosition.ptr());
            glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
            glPopMatrix();
            return matrix;

        }

        void preparation(float rotX, float rotY, float rotZ){
            constexpr float PI_DIV_180 = 3.1415 / 180.0f;
            
            Matrix4 basicRotate;
            Qued qued;
            // axis primal vectors
            Vec3 fromX(1, 0, 0);
            Vec3 fromY(0, 1, 0);
            Vec3 fromZ(0, 0, 1);
            // new position vectors
            Vec3 toX(cos(rotX * PI_DIV_180), sin(rotX * PI_DIV_180), 0);
            Vec3 toY(0, cos(rotY * PI_DIV_180), sin(rotY * PI_DIV_180));
            Vec3 toZ(sin(rotZ * PI_DIV_180), 0, cos(rotZ * PI_DIV_180));

            // make new rotate matrix
            qued.newQued(fromX, toX);
            basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));
            qued.newQued(fromY, toY);
            basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));
            qued.newQued(fromZ, toZ);
            basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));

            // push new matrix
            rotationPosition = multiplyMatrix(rotationPosition, basicRotate);
        }

        virtual ~Object(){};
};