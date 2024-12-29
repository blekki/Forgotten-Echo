#include <vector>

#include "particlebox.h"
#include "structures/xyz.h"

using namespace std;

void ParticleBox::generate(){
    for (int i = 0; i < PARTICLE_COUNT; i++){
        xyz_t particle;
        // range between (-1.0 * radius) and (1.0 * radius)
        int maxNum = 200 * radius + 1;
        int reduce = 100 * radius;

        particle.x = (rand() % maxNum - reduce) / 100.0f;
        particle.y = (rand() % maxNum - reduce) / 100.0f;
        particle.z = (rand() % maxNum - reduce) / 100.0f;
        particleGroup.push_back(particle);
    }
}

void ParticleBox::setBoxPosition(float x, float y, float z){
    differPos.x = x - position.x;
    differPos.y = y - position.y;
    differPos.z = z - position.z;
    position.x = x;
    position.y = y;
    position.z = z;
}

void ParticleBox::checkPosition(xyz_t *particle, xyz_t differPos){
    particle->x -= differPos.x;
    particle->y -= differPos.y;
    particle->z -= differPos.z;
}

void ParticleBox::normalizeToRadius(xyz_t *particle, float distance){
    float coef = radius / sqrt(distance);
    particle->x -= particle->x * coef * 2;
    particle->y -= particle->y * coef * 2;
    particle->z -= particle->z * coef * 2;
}
void ParticleBox::drawparticle(){
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < PARTICLE_COUNT; i++){
        ParticleBox::checkPosition(&particleGroup.at(i), differPos);
        
        //checking if particle out the range (out of radius)
        float distance = particleGroup.at(i).x * particleGroup.at(i).x +
                            particleGroup.at(i).y * particleGroup.at(i).y +
                            particleGroup.at(i).z * particleGroup.at(i).z;
        if (distance > radius * radius)
            ParticleBox::normalizeToRadius(&particleGroup.at(i), distance);

        glVertex3f(particleGroup.at(i).x, particleGroup.at(i).y, particleGroup.at(i).z);

    }
    differPos.x = 0;
    differPos.y = 0;
    differPos.z = 0;
    glEnd();
}