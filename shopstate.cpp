#include "iostream"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include "shopstate.h"

using namespace std;

void Shopstate::prerender(){
    return;
}

void Shopstate::render(){
    glColor3f(0.1, 0.1, 0.1);
    glOrtho(0, 1, 0, 1, -1, 1);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glEnd();

    cursor.draw();
}

Shopstate::Shopstate(){
    // shopTextureID = SOIL_load_OGL_texture("+", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    // glBindTexture (GL_TEXTURE_2D, shopTextureID);
    // glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glBindTexture (GL_TEXTURE_2D, 0);
    // cout << "shopstate::setTexture: " << shopTextureID << endl;
}