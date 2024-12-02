#include <iostream>
#include <stdlib.h>
#include <cmath>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <GL/glut.h>

#include "sphere.h"
#include "planet.h"
// #include <glad/glad.h>


using namespace std;

//<><><> NEEDY CONSTANTS
const float PiDiv180 = 3.1415f / 180.0f;
int width{600};
int height{400};

int textureID[2];
int sphere[3];
float centrePoint[3] {2.0f, 0.0f, 0.0f};

// Planet mars;

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
//draw simple 2d triangle
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

void sphereCap(int section, int position)
{
    //position means where hat must be created.
    //   "1" - upper
    //   "-1" - lower

    float stk = (1.57f - 3.14f / (float)section) * position; //1.57 = pi/2

    glColor3f(1.0f, 1.0f * position, 0.0f); //unneedy color changer (was added only for testing)

    //create sphere caps
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 1.0f * position, 0.0f); //pole point
    //other section line points
    for(int sector = 0; sector <= section; sector++){
        float sec = (6.28f * (float)sector / (float)section) * position; //6.28 = pi * 2
        glVertex3f(cos(stk) * cos(sec), sin(stk), cos(stk) * sin(sec));
    }
    glEnd();
}

void createSphere(int section)
{
    //upper pole
    sphereCap(section, 1);

    for (int stack = 1; stack < section - 1; stack++){ // sections up to down
        glBegin(GL_QUAD_STRIP);
        for (int sector = 0; sector <= section; sector++){ // sections around
            float stk = 1.57f - 3.14f * (float)stack / (float)section;  //1.57 = pi/2
            float sec = 6.28f * (float)sector / (float)section;         //6.28 = pi * 2
            
            glColor3f(0.1f * sector, 0.1f * sector, 0.1f * sector);
            glVertex3f(cos(stk) * cos(sec), sin(stk), cos(stk) * sin(sec));
            //next stack line point
            stk = 1.57f - 3.14f * (float)(stack + 1) / (float)section;
            glVertex3f(cos(stk) * cos(sec), sin(stk), cos(stk) * sin(sec));
        }
        glEnd();
    }

    //lower pole
    sphereCap(section, -1);
}

void createList(int id){
    sphere[id] = glGenLists(id);
    glNewList(sphere[id], GL_COMPILE);
    // triangleSphere(5);
    glEndList();
}

void matrix(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.2f, 0.0f, 0.0f);
}


//##############################################
//<><><><><><><><> MAIN PROGRAM <><><><><><><><>
int main(void)
{
    // check did glfw run or not
    if (!glfwInit())
    {
        cout << "error: glfw didn'd run" << endl;
        exit(EXIT_FAILURE);
    }

    // time and fps
    double time = glfwGetTime();
    glfwSwapInterval(1);

    // create window
    GLFWwindow *basicWindow = glfwCreateWindow(width, height, "Basic Window", NULL, NULL);
    if (!basicWindow)
    {
        cout << "error: window can't be created" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(basicWindow);
    // size of window
    glfwGetFramebufferSize(basicWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // set coordinates system for window
    glLoadIdentity();
    glOrtho(-((float)width / (float)height), ((float)width / (float)height), -1, 1, -1, 1);

    // mars.setPosition();
    // mars.setTexture();


    //add texture
    textureID[0] = SOIL_load_OGL_texture("./solarsystemscope/2k_moon.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    cout << "texture 1: " << textureID[0] << endl;
    textureID[1] = SOIL_load_OGL_texture("./solarsystemscope/2k_mars.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    cout << "texture 2: " << textureID[1] << endl;

    //enable gl functions
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, width / (float) height, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    Planet mars;
    mars.setTexture("./solarsystemscope/2k_mars.jpg");
    mars.setPosition(3.0f, 4.0f, 0.0f);


    // loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(basicWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // createCircle(0.0f, 0.0f, 1.0f);
        // createTriangle();
        // createSphere(100);

        // sphere.draw(5);
        mars.draw();

        // if (sphere[1] == 0){
        //     sphere[1] = glGenLists(2);
        //     glNewList(sphere[1], GL_COMPILE);
        //     triangleSphere(0);
        //     glEndList();
        // }
        // glCallList(sphere[1]);

        // matrix();


        // rotate object and change that position
        // glLoadIdentity();
        // glTranslated(0.0f, 0.0f, -0.008f);
        // angle += 0.01;
        glRotated(0.2f, 0.0f, 1.0f, 0.0f);

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
