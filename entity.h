#pragma once
#include "shader/brightness.h"
#include "matrices.h"

class Entity
{
    protected:
        string name;
        xyz_t position;
        Matrix4 rotation; // todo: rename to rotation (rotate)
        static RotationMatrixPack coupleMatrices; //error with static

    // private:
        Brightness brightnessShader;

    public:
        void setPosition(float x, float y, float z);
        // void setRotate(float angleX); 
        float getX();
        float getY();
        float getZ();
        xyz_t getXYZ();
        Matrix4 getRotation();

        void prepareRotation(float rotX, float rotY, float rotZ);

        // function for rotate object
        void addRotateMatrix(Matrix4 matrix){
            rotation = multiplyMatrix(rotation, matrix);
        }

        void addTranslateVec(Vec3 vec){
            Vec3 translateVec = multiplyMatrixVec(rotation, vec);
            position.x += translateVec.x / 5.0f;
            position.y += translateVec.y / 5.0f;
            position.z += translateVec.z / 5.0f;
        }

        void preparation(float rotX, float rotY, float rotZ){ // todo: rename setEulerRotation
            prepareRotation(rotX, rotY, rotZ);
        }

        // use rotation matrices
        void roll(bool cw){
            addRotateMatrix(coupleMatrices.getRoll(cw));
        }

        void yaw(bool cw){
            addRotateMatrix(coupleMatrices.getYaw(cw));
        }
        
        void pitch(bool up){
            addRotateMatrix(coupleMatrices.getPitch(up));
        }

        void shift(float x, float y, float z){
            addTranslateVec(Vec3(x,y,z));
        }

        Entity(){
            // brightnessShader.init();
        };
};