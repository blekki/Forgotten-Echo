#include <iostream>
#include <stdlib.h>
#include <cmath>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <GL/glu.h>
// #include <glad/glad.h>

#include "primal.h"
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

// int textureID[2];
// int sphere[3];
// float centrePoint[3] {2.0f, 0.0f, 0.0f};
int actionStatus = 0;

//<><><> FUNCTIONS <><><>
void keyAction(string logs, int actionType){
    cout << logs << endl;
    actionStatus = actionType;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) // call actions if key pressed
{
    if (key == 256 && action == 1) {
        cout << "action: window was closed" << endl;
        glfwSetWindowShouldClose(window, true);
    }

    //keys right and left
    if (key == GLFW_KEY_Q && (action == 2 || action == 1))
        keyAction("action: key Q", 1);
    if (key == GLFW_KEY_E && (action == 2 || action == 1))
        keyAction("action: key E", 2);

    //keys up and down
    if (key == GLFW_KEY_RIGHT && (action == 2 || action == 1))
        keyAction("action: key right", 3);
    if (key == GLFW_KEY_LEFT && (action == 2 || action == 1))
        keyAction("action: key left", 4);

    //keys E and Q
    if (key == GLFW_KEY_UP && (action == 2 || action == 1))
        keyAction("action: key up", 5);
    if (key == GLFW_KEY_DOWN && (action == 2 || action == 1))
        keyAction("action: key down", 6);

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
        cout << "error: glfw didn't run" << endl;
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

    Primal primalObj;

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

        // a few actions for rotation an our object
        if (actionStatus == 1)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(true));
        if (actionStatus == 2)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(false));
        
        if (actionStatus == 3)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(true));
        if (actionStatus == 4)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(false));
        
        if (actionStatus == 5)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(true));
        if (actionStatus == 6)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(false));
            
        spaceship.draw();
        // testing();

        // other needy actions
        actionStatus = 0;
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
