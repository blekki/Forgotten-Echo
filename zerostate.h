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
        virtual void prerender() = 0;
        virtual void pushActionStatus(int actionStatus) = 0;
        virtual void render() = 0;
        Cursor* getCursorPtr();
        void pushWindowLink(GLFWwindow *window);

        Zerostate(){
            screen_width = 600;
            screen_height = 400;
        }
};