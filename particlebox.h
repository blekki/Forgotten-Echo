#pragma once
#include <cstdlib>
#include <vector>

#include <GL/gl.h>
#include "qued.h"

#include "structures/xyz.h"

using namespace std;

// constants
const int PARTICLE_COUNT = 1000;

class ParticleBox{
    private:
        float radius = 10;
        xyz_t position {0, 0, 0};
        xyz_t differPos {0, 0, 0};

        vector<xyz_t> particleGroup;

        void setBoxPosition(float x, float y, float z);
        void drawparticle();
        void checkPosition(xyz_t *particle, xyz_t differPos);
        void normalizeToRadius(xyz_t *particle, float distance);
        void generate();

    public:
        void newGenerate(){
                generate();
        }

        void newBoxPosition(float x, float y, float z){
            setBoxPosition(x, y, z);
        }

        void draw(){
            glPushMatrix();
            glTranslatef(position.x, position.y, position.z);
            drawparticle();
            glPopMatrix();
        }
};