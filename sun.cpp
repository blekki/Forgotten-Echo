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

Matrix4 Sun::makeModelMatrix(xyz_t follow){
    Matrix4 matrix;
    glPushMatrix();
    glLoadIdentity();
    // glTranslated(position.x + follow.x, position.y + follow.y, position.z + follow.z);
    glTranslatef(position.x, position.y, position.z);
    glScalef(scale, scale, scale);
    glMultMatrixf(rotation.ptr());
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
    glPopMatrix();
    return matrix;
}

void Sun::prerender(SunShader &sunShader){
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, 256, 256);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glUseProgram(sunShader.getShaderID());
    sunShader.setTime(glfwGetTime());
    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(-1,  1);
    glVertex2f( 1,  1);
    glVertex2f( 1, -1);
    glEnd();
    glUseProgram(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// draw a triangle with shader texture
void Sun::draw(xyz_t follow){
    Vec3 from(0, 0, -1);
    Vec3 to(position.x, position.y, position.z);
    to.normalize();
    Qued qued;
    qued.newQued(from, to);
    Matrix4 newRotation;
    newRotation = rotationMatrix(qued);

    Vec3 v1(-1.0,  1.0, 0);
    Vec3 v2(-1.0, -1.0, 0);
    Vec3 v3(1.0, -1.0, 0);
    Vec3 v4(1.0,  1.0, 0);

    Vec3 realVec1 = multiplyMatrixVec(newRotation, v1);
    Vec3 realVec2 = multiplyMatrixVec(newRotation, v2);
    Vec3 realVec3 = multiplyMatrixVec(newRotation, v3);
    Vec3 realVec4 = multiplyMatrixVec(newRotation, v4);

    glBindTexture(GL_TEXTURE_2D, coronaTexture);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(position.x + follow.x, position.y + follow.y, position.z + follow.z);
    glScalef(scale, scale, scale);
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
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, 0);
}

Sun::Sun(){
    glGenTextures(1, &coronaTexture);
    glBindTexture(GL_TEXTURE_2D, coronaTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, coronaTexture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}