#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "cursor.h"

class Zerostate
{
    protected:
        GLFWwindow *windowLink;
        int screen_width;
        int screen_height;

        Cursor cursor;
    
    public:
        Cursor* getCursorPtr();
        void pushWindowLink(GLFWwindow *window);

        Zerostate(){
            cursor.loadTexture("models/Light Interceptor-T/engine_back.bmp");
            screen_width = 600;
            screen_height = 400;
        }
};