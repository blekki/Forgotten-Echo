#include <iostream>
#include <stdlib.h>
#include <cmath>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

#include "planet.h"

//change basic planet variables (characteristics)
void Planet::setPosition(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Planet::setRotateSpeed(float rotateSpeed){
    this->rotateSpeed = rotateSpeed;
}

void Planet::setScale(float scale){
    this->scale = scale;
}

void Planet::setTexture(char* texture){
    textureID = SOIL_load_OGL_texture(texture, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    cout << "setTexture: " << textureID << endl;
}

//draw a triangle with texture
void Planet::vertex(float a[]){
    float x = a[0];
    float y = a[1];
    float z = a[2];

    float phi = 1.0f - (1.0f + atan2(x, -z) / 3.1415f) / 2.0f;
    float theta = acos(y) / 3.1415f;

    glTexCoord2f(phi, theta);
    Sphere::vertex(a);
}

void Planet::draw(){
    if (ID == 0){
            ID = glGenLists(1);
            glNewList(ID, GL_COMPILE);
            Sphere::draw();
            glEndList();
    }
    glColor3f(1.0f, 1.0f, 1.0f);
    

    glPushMatrix();
    // glRotatef(this->orbitSpeed * glfwGetTime(), 0.0f, 1.0f, 0.0f); // orbit rotate
    glScalef(scale, scale, scale);
    glTranslated(x, y, z);
    glRotatef(this->rotateSpeed * glfwGetTime(), 0.0f, 1.0f, 0.0f); // rotate around itself

    glBindTexture(GL_TEXTURE_2D, ID);
    glCallList(ID);
    glPopMatrix();
}