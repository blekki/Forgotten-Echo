#pragma once
#include <cstdlib>
#include <vector>

#include <GL/gl.h>
#include "qued.h"

#include "structures/xyz.h"

using namespace std;

// constants
const int PARTICLE_COUNT = 1000;

// class Particle{
//     public:
//         xyz_t position;
    
//         void generate(int radius);
// };

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
        // void generate(xyz_t *particle);
        void generate();

    public:
        void newGenerate(){
            // Particle particle;
            // for (int i = 0; i < PARTICLE_COUNT; i++){
                // particle.generate(radius);
                // generate(&particleGroup.at(i));
                // particleGroup.push_back(particle);
                generate();
            // }
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