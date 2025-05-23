#pragma once

#include "qued.h"

class RotationMatrixPack //todo: rename
{
    private:
        Matrix4 cwRoll;
        Matrix4 ccwRoll;
        Matrix4 cwYaw;
        Matrix4 ccwYaw;
        Matrix4 upPitch;
        Matrix4 downPitch;

        void declareMatrix(Matrix4* matrix4, Matrix4* opposMatrix4, Vec3 from, Vec3 to);

    public:
        Matrix4 getRoll(bool whatKindSide){
            return (whatKindSide ? cwRoll : ccwRoll);
        }

        Matrix4 getYaw(bool whatKindSide){
            return (whatKindSide ? cwYaw : ccwYaw);
        }

        Matrix4 getPitch(bool whatKindSide){
            return (whatKindSide ? upPitch : downPitch);
        }

        RotationMatrixPack(){
            Vec3 vecRight   {1, 0, 0};
            Vec3 vecUp      {0, 1, 0};
            Vec3 vecForward {0, 0, -1};

            declareMatrix(&cwRoll, &ccwRoll, vecUp, vecRight);
            declareMatrix(&cwYaw, &ccwYaw, vecForward, vecRight);
            declareMatrix(&upPitch, &downPitch, vecForward, vecUp);
        };
};