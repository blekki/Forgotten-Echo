#pragma once
#include <cstdlib>
#include <vector>

#include <GL/gl.h>
#include "qued.h"

using namespace std;

// constants
const int PARTICLE_COUNT = 2000;

struct xyz_t{
    float x;
    float y;
    float z;
};

class Particle{
    public:
        xyz_t position;
    
        void generate(int radius);
};

class ParticleBox{
    private:
        float radius = 20;
        xyz_t position {0, 0, 0};
        xyz_t differPos {0, 0, 0};

        vector<Particle> particleGroup;

        void setBoxPosition(float x, float y, float z);
        void drawparticle();
        void checkPosition(Particle *particle, xyz_t differPos);
        void normalizeToRadius(Particle *particle, float distance);

    public:
        void newGenerate(){
            Particle particle;
            for (int i = 0; i < PARTICLE_COUNT; i++){
                particle.generate(radius);
                particleGroup.push_back(particle);
            }
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