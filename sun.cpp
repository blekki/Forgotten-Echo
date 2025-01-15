#include <iostream>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <GL/glu.h>

#include "sun.h"

void Sun::setScale(float scale){
    this->scale = scale;
}

Matrix4 Sun::makeModelMatrix(){
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
void Sun::draw(){
    Vec3 from(0, 0, -1);
    Vec3 to(position.x, position.y, position.z);
    to.normalize();
    Qued qued;
    qued.newQued(from, to);
    Matrix4 newRotation;
    newRotation = rotationMatrix(qued);

    Vec3 v1(-1.0,  1.0, -10);
    Vec3 v2(-1.0, -1.0, -10);
    Vec3 v3(1.0, -1.0, -10);
    Vec3 v4(1.0,  1.0, -10);

    Vec3 realVec1 = multiplyMatrixVec(newRotation, v1);
    Vec3 realVec2 = multiplyMatrixVec(newRotation, v2);
    Vec3 realVec3 = multiplyMatrixVec(newRotation, v3);
    Vec3 realVec4 = multiplyMatrixVec(newRotation, v4);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(realVec1.x, realVec1.y, realVec1.z);
    glTexCoord2f(0, 1);
    glVertex3f(realVec2.x, realVec2.y, realVec2.z);
    glTexCoord2f(1, 1);
    glVertex3f(realVec3.x, realVec3.y, realVec3.z);
    glTexCoord2f(1, 0);
    glVertex3f(realVec4.x, realVec4.y, realVec4.z);
    glEnd();
}