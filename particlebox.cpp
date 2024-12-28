#include <vector>

#include "particlebox.h"

using namespace std;

void Particle::generate(int radius){
    // range between -1.0 and 1.0
    int maxNum = 200 * radius + 1;
    int reduce = 100 * radius;
    position.x = (rand() % maxNum - reduce) / 100.0f;
    position.y = (rand() % maxNum - reduce) / 100.0f;
    position.z = (rand() % maxNum - reduce) / 100.0f;
}

void ParticleBox::setBoxPosition(float x, float y, float z){
    differPos.x = x - position.x;
    differPos.y = y - position.y;
    differPos.z = z - position.z;
    position.x = x;
    position.y = y;
    position.z = z;
}

void ParticleBox::checkPosition(Particle *particle, xyz_t differPos){
    particle->position.x -= differPos.x;
    particle->position.y -= differPos.y;
    particle->position.z -= differPos.z;
}

void ParticleBox::normalizeToRadius(Particle *particle, float distance){
    float coef = radius / sqrt(distance);
    xyz_t vec;
    vec.x = particle->position.x * coef;
    vec.y = particle->position.y * coef;
    vec.z = particle->position.z * coef;
    particle->position.x -= vec.x * 2;
    particle->position.y -= vec.y * 2;
    particle->position.z -= vec.z * 2;
}
void ParticleBox::drawparticle(){
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < PARTICLE_COUNT; i++){
        ParticleBox::checkPosition(&particleGroup.at(i), differPos);
        
        //checking if particle out the range (radius)
        float distance = particleGroup.at(i).position.x * particleGroup.at(i).position.x +
                            particleGroup.at(i).position.y * particleGroup.at(i).position.y +
                            particleGroup.at(i).position.z * particleGroup.at(i).position.z;
        if (distance > radius * radius)
            ParticleBox::normalizeToRadius(&particleGroup.at(i), distance);

        glVertex3f(particleGroup.at(i).position.x, particleGroup.at(i).position.y, particleGroup.at(i).position.z);

    }
    differPos.x = 0;
    differPos.y = 0;
    differPos.z = 0;
    glEnd();
}