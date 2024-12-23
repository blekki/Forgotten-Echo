#include <iostream>
#include <stdlib.h>
#include <cmath>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <GL/glu.h>
// #include <glad/glad.h>

#include "sphere.h"
#include "planet.h"
#include "model.h"
#include "object.h"



using namespace std;

//<><><> NEEDY CONSTANTS
const float PiDiv180 = 3.1415f / 180.0f;
// const char* MODELS_DIRECTORY = "models/";
int width{600};
int height{400};

int textureID[2];
int sphere[3];
float centrePoint[3] {2.0f, 0.0f, 0.0f};

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
    for (int i = 0; i < 360; i++) {
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
    for (int sector = 0; sector <= section; sector++) {
        float sec = (6.28f * (float)sector / (float)section) * position; //6.28 = pi * 2
        glVertex3f(cos(stk) * cos(sec), sin(stk), cos(stk) * sin(sec));
    }
    glEnd();
}

void createSphere(int section)
{
    //upper pole
    sphereCap(section, 1);

    for (int stack = 1; stack < section - 1; stack++) { // sections up to down
        glBegin(GL_QUAD_STRIP);
        for (int sector = 0; sector <= section; sector++) { // sections around
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

// class Vec{
//     public:
//         float x;
//         float y;

//         Vec& operator-(const Vec& other){
//             x -= other.x;
//             y -= other.y;
//             return *this;
//         }
//         Vec& operator+(const Vec& other){
//             x += other.x;
//             y += other.y;
//             return *this;
//         }
//         Vec& operator/(const float other){
//             x /= other;
//             y /= other;
//             return *this;
//         }
//         Vec& operator*(const float other){
//             x *= other;
//             y *= other;
//             return *this;
//         }
//         void print(){
//             cout << x << " : " << y << endl;
//         }
//         void normalize(){
//             float coef = 1.0f / sqrt(x * x + y * y);
//             x *= coef;
//             y *= coef;
//         }
// };

void testing(){

}

//##############################################
//<><><><><><><><> MAIN PROGRAM <><><><><><><><>
int main(void)
{
    // check did glfw run or not
    if (!glfwInit()) {
        cout << "error: glfw didn'd run" << endl;
        exit(EXIT_FAILURE);
    }

    // time and fps
    glfwSetTime(0.0f);
    // double time = glfwGetTime();
    glfwSwapInterval(1);

    // create window
    GLFWwindow *basicWindow = glfwCreateWindow(width, height, "Basic Window", NULL, NULL);
    if (!basicWindow) {
        cout << "error: window can't be created" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(basicWindow);

    //enable gl functions
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);

    //basic matrixes
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, width / (float) height, 0.1f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f,
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    //planets creating
    Planet mars;
    mars.setTexture("solarsystemscope/2k_mars.jpg");
    mars.setScale(1.0f);
    mars.setPosition(0.0001f, 0.0f, 0.0f);
    mars.setRotateSpeed(40.0f);

    Planet moon;
    moon.setTexture("solarsystemscope/2k_moon.jpg");
    moon.setScale(0.4f);
    moon.setPosition(5.0f, 0.0f, 0.0f);
    moon.setRotateSpeed(-13.0f);

    Object spaceship;
    // spaceship.newModel("models/Carrier-T.obj");
    // spaceship.newMaterials("models/Carrier-T.mtl");
    spaceship.newModel("models/Turanic Raiders/Raiders Ion Array Frigate/lod0/P1ionarrayfrigate.obj");
    spaceship.newMaterials("models/Turanic Raiders/Raiders Ion Array Frigate/lod0/P1ionarrayfrigate.mtl");
    spaceship.setScale(0.02f);
    spaceship.setRotate(8.0f);
    // spaceship.draw();

    // prepering everything for rotationMatrices
    rotMatrices coupleMatrices;
    coupleMatrices.newMatrices();

    // loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(basicWindow))
    {
        // size of window
        glfwGetFramebufferSize(basicWindow, &width, &height);
        glViewport(0, 0, width, height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // mars.draw();
        // moon.draw();
        spaceship.addRotateMatrix(coupleMatrices.getRoll());
        // spaceship.addRotateMatrix(coupleMatrices.getYaw());
        spaceship.addRotateMatrix(coupleMatrices.getPitch());
        spaceship.draw();
        // testing();

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();

    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
