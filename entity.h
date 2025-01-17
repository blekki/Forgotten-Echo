#pragma once
#include "shader/brightness.h"
#include "matrices.h"

class Entity
{
    protected:
        string name;
        xyz_t position;
        Matrix4 rotation;
        static RotationMatrixPack coupleMatrices;

    // private:
        Brightness brightnessShader;

    public:
        void setPosition(float x, float y, float z);
        // void setRotate(float angleX); 
        virtual float getX();
        virtual float getY();
        virtual float getZ();
        virtual xyz_t getXYZ();
        Matrix4 getRotation();

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

        void setRotatationPosition(float x, float y, float z);

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