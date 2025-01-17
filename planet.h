#pragma once
#include "structures/xyz.h"
#include "shader/planetShader.h"

#include "sphere.h"
#include "entity.h"

using namespace std;

class Planet: public Entity, public Sphere
{
    private:
        int ID = 0;
        int textureID = 0;
        //other characteristics
        float scale = 1.0f;
        float orbitSpeed = 30.0f;
        float rotateSpeed = 0.0001f;

    public:
        void setTexture(string texture);
        void setRotateSpeed(float rotateSpeed);
        void setScale(float radius);
        Matrix4 makeModelMatrix(xyz_t follow);
        
        void draw(PlanetShader planetShader, xyz_t follow){
            planetShader.setModelMatrix(makeModelMatrix(follow));
            draw();
        }

        virtual void draw() override;
        
    protected:
        virtual void vertex(float a[]) override;
};