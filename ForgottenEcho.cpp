#include <iostream>
#include <stdlib.h>
#include <cmath>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
// #include <glad/glad.h>

using namespace std;

//<><><> NEEDY CONSTANTS
const float PiDiv180 = 3.1415f / 180.0f;

//<><><> FUNCTIONS <><><>
// call actions if key pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == 256 && action == 1)
    {
        cout << "logs: window was closed" << endl;
        glfwSetWindowShouldClose(window, true);
    }
}
// coef for x coordinate
float coefX(float x)
{
    return (x / 1.5);
}

// draw a 2d circle
void createCircle(float x, float y, float radius)
{ // x and y means centre of circle
    // glColor3f(1.0f, 1.0f, 1.0f); //white color
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++)
    {
        x = radius * cos(i * PiDiv180);
        y = radius * sin(i * PiDiv180);
        glColor3f(x, y, 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}
// draw simple 2d triangle
void createTriangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}

void sphereCap(int section)
{
    //there must be code creating sphere caps using GL_TRIANGLE_FAN
}

//!!! ПОТРІБНО ДОРОБИТИ !!!
void createSphere(int section)
{
    for (int stack = 0; stack < section; stack++)
    { // sections up to down
        glBegin(GL_QUAD_STRIP);

        for (int sector = 0; sector <= section; sector++)
        { // sections around
            glColor3f(0.1f * sector, 0.1f * sector, 0.1f * sector);

            float sec = 6.28f * (float)sector / (float)section;
            float stk = 1.57f - 3.14f * (float)stack / (float)section;

            glVertex3f(cos(stk) * cos(sec), cos(stk) * sin(sec), sin(stk));
            stk = 1.57f - 3.14f * (float)(stack + 1) / (float)section;
            glVertex3f( cos(stk) * cos(sec), cos(stk) * sin(sec), sin(stk));

        }
        glEnd();
    }
}

//<><><><><> MAIN PROGRAM <><><><><>
int main(void)
{
    // check does glfw run or not
    if (!glfwInit())
    {
        cout << "error: glfw didn'd run" << endl;
        exit(EXIT_FAILURE);
    }

    // time and fps
    double time = glfwGetTime();
    glfwSwapInterval(1);

    int width{600};
    int height{400};

    // create window
    GLFWwindow *basicWindow = glfwCreateWindow(width, height, "Basic Window", NULL, NULL);
    if (!basicWindow)
    {
        cout << "error: window can't be created" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(basicWindow);

    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);

    // size of window
    glfwGetFramebufferSize(basicWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // set coordinates system for window
    glLoadIdentity();
    glOrtho(-((float)width / (float)height), ((float)width / (float)height), -1, 1, -1, 1);

    // loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(basicWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // createCircle(0.0f, 0.0f, 1.0f);
        // createTriangle();
        createSphere(15);

        // rotate object and change that position
        //  glTranslated(cos(angle) / 100.0f, 0.0f, 0.0f);
        //  angle += 0.01;
        glRotated(1.0f, 1.0f, 1.0f, 1.0f);
        

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
