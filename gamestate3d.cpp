#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <GL/glu.h>

#include "gamestate3d.h"

void Gamestate3d::prepareMatrix(){
    glfwGetFramebufferSize(windowLink, &screen_width, &screen_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0f, screen_width / (float) screen_height, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

