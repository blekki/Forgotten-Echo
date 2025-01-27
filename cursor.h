#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

class Cursor
{
    private:
        double x;
        double y;
        int textureID;

        // screen size
        int screen_width;
        int screen_height;

    public:
        void setX(double x);
        void setY(double y);
        void loadTexture(string path);
        void pushWindowSize(GLFWwindow *window);
        double getX();
        double getY();
        double getTransformX();
        double getTransformY();

        void printXY(); // todo: remove

        void draw();

        Cursor(){
            x = 0;
            y = 0;
            textureID = 0;
        }
};