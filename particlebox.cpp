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
    deltaPos.x = x - position.x;
    deltaPos.y = y - position.y;
    deltaPos.z = z - position.z;
    position.x = x;
    position.y = y;
    position.z = z;
}

void ParticleBox::changePosition(xyz_t *particle, xyz_t deltaPos){
    particle->x -= deltaPos.x;
    particle->y -= deltaPos.y;
    particle->z -= deltaPos.z;
}

void ParticleBox::doubleReplaceParticles(xyz_t *particle, float distance){
    float coef = radius / sqrt(distance);
    particle->x -= particle->x * coef * 2;
    particle->y -= particle->y * coef * 2;
    particle->z -= particle->z * coef * 2;
}
void ParticleBox::drawparticle(){
    glPointSize(2);
    // glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < PARTICLE_COUNT; i++){
        ParticleBox::changePosition(&particleGroup.at(i), deltaPos);
        
        //checking if particle out the range (out of radius)
        float distance = particleGroup.at(i).x * particleGroup.at(i).x +
                         particleGroup.at(i).y * particleGroup.at(i).y +
                         particleGroup.at(i).z * particleGroup.at(i).z;
        if (distance > radius * radius)
            ParticleBox::doubleReplaceParticles(&particleGroup.at(i), distance);

        glVertex3f(particleGroup.at(i).x, particleGroup.at(i).y, particleGroup.at(i).z);

    }
    deltaPos.x = 0;
    deltaPos.y = 0;
    deltaPos.z = 0;
    glEnd();
}