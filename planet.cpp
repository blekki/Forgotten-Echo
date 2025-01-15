#include <iostream>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <GL/glu.h>

#include "planet.h"

void Planet::setRotateSpeed(float rotateSpeed){
    this->rotateSpeed = rotateSpeed;
}

void Planet::setScale(float scale){
    this->scale = scale;
}

void Planet::setTexture(string texture){
    textureID = SOIL_load_OGL_texture(texture.c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    glBindTexture (GL_TEXTURE_2D, textureID);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture (GL_TEXTURE_2D, 0);
    cout << "setTexture: " << textureID << endl;
}

Matrix4 Planet::makeModelMatrix(){
    Matrix4 matrix;
    glPushMatrix();
    glLoadIdentity();
    glTranslated(position.x, position.y, position.z);
    glScalef(scale, scale, scale);
    glMultMatrixf(rotation.ptr());
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
    glPopMatrix();
    return matrix;
}

//draw a triangle with texture
void Planet::vertex(float a[]){
    // float x = a[0];
    // float y = a[1];
    // float z = a[2];

    // float phi = 1.0f - (1.0f + atan2(x, -z) / 3.1415f) / 2.0f;
    // float theta = acos(y) / 3.1415f;

    // glTexCoord2f(phi, theta);
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
    

    // // glRotatef(this->orbitSpeed * glfwGetTime(), 0.0f, 1.0f, 0.0f); // orbit rotate
    // glRotatef(this->rotateSpeed * glfwGetTime(), 0.0f, 1.0f, 0.0f); // rotate around itself

    glBindTexture(GL_TEXTURE_2D, textureID);
    glCallList(ID);
    // glPopMatrix();
}