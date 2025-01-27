#include "iostream"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include "ForgottenEcho.h"

#include "cursor.h"

void Cursor::setX(double x){
    this->x = x;
}
void Cursor::setY(double y){
    this->y = y;
}

void Cursor::pushWindowSize(GLFWwindow *window){
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
}

void Cursor::loadTexture(string path){
    textureID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    glBindTexture (GL_TEXTURE_2D, textureID);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture (GL_TEXTURE_2D, 0);
    cout << "cursor::setTexture: " << textureID << endl;
}

double Cursor::getX(){
    return x;
}
double Cursor::getY(){
    return y;
}

double Cursor::getTransformX(){
    return (x - (screen_width / 2.0f));
}
double Cursor::getTransformY(){
    return (y - (screen_height / 2.0f));
}

void Cursor::printXY(){
    cout << getTransformX() << " : " << getTransformY() << endl;
}

void Cursor::draw(){
    // glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, screen_width, screen_height, 0, -1, 1);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(x, y, 0);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(-10, 10);
    glTexCoord2f(0, 1);
    glVertex2f(-10, -10);
    glTexCoord2f(1, 1);
    glVertex2f(10, -10);
    glTexCoord2f(1, 0);
    glVertex2f(10, 10);
    
    glEnd();
    glPopMatrix();
}
