#pragma once
#include <cstdlib>
#include <vector>

#include <GL/gl.h>
#include "qued.h"

#include "structures/xyz.h"

using namespace std;

// constant
// const int PARTICLE_COUNT = 200;

class ParticleBox{
    private:
        const int PARTICLE_COUNT = 300;
        float radius = 15;
        xyz_t position {0, 0, 0};
        xyz_t deltaPos {0, 0, 0};

        vector<xyz_t> particleGroup;

        void setBoxPosition(float x, float y, float z);
        void drawparticle();
        void changePosition(xyz_t *particle, xyz_t differPos);
        void doubleReplaceParticles(xyz_t *particle, float distance);
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