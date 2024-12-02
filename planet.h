#pragma once

#include "sphere.h"

using namespace std;

class Planet: Sphere{
    private:
        int ID = 0;
        int textureID = 0;
        //position 
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        //other characteristics
        float scale = 1.0f;
        float orbitSpeed = 3.0f;
        float rotateSpeed = 0.1f;

    public:
        void setTexture(char* texture);
        void setPosition(float x, float y, float z);
        void setRotateSpeed(float rotateSpeed);
        void setScale(float radius);

        virtual void draw() override;
        
    protected:
        virtual void vertex(float a[]) override;
};