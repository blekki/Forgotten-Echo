#pragma once

#include <math.h>

class Vec3{
    public:
        float x;
        float y;
        float z;

    public:
        Vec3(){
            float x = 0;
            float y = 0;
            float z = 0;
        };

        Vec3(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vec3 operator-(const Vec3& other){
            Vec3 newVec;
            newVec.x = other.x - x;
            newVec.y = other.y - y;
            newVec.z = other.z - z;
            return newVec;
        }

        Vec3 operator+(const Vec3& other){
            Vec3 newVec;
            newVec.x = x + other.x;
            newVec.y = y + other.y;
            newVec.z = z + other.z;
            return newVec;
        }

        Vec3& operator/(const float other){
            x /= other;
            y /= other;
            z /= other;
            return *this;
        }

        void normalize(){
            float coef = 1.0f / sqrt((x * x) + (y * y) + (z * z));
            x *= coef;
            y *= coef;
            z *= coef;
        }
};