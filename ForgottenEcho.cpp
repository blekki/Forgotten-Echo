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

// save action type (rotate direction). Change when concrete key was pressed
enum action_t{
    ACTION_NOTHING,
    ACTION_ROLL_CW,
    ACTION_ROLL_CCW,
    ACTION_YAW_CW,
    ACTION_YAW_CCW,
    ACTION_PITCH_UP,
    ACTION_PITCH_DOWN,
};
action_t actionStatus = ACTION_NOTHING;

//<><><> FUNCTIONS <><><>
void keyAction(string logs, action_t actionType){
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
        keyAction("action: key Q", ACTION_ROLL_CW);
    if (key == GLFW_KEY_E && (action == 2 || action == 1))
        keyAction("action: key E", ACTION_ROLL_CCW);

    //keys up and down
    if (key == GLFW_KEY_RIGHT && (action == 2 || action == 1))
        keyAction("action: key right", ACTION_YAW_CW);
    if (key == GLFW_KEY_LEFT && (action == 2 || action == 1))
        keyAction("action: key left", ACTION_YAW_CCW);

    //keys E and Q
    if (key == GLFW_KEY_UP && (action == 2 || action == 1))
        keyAction("action: key up", ACTION_PITCH_UP);
    if (key == GLFW_KEY_DOWN && (action == 2 || action == 1))
        keyAction("action: key down", ACTION_PITCH_DOWN);

}

void testing(){
    //###
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
        if (actionStatus == ACTION_ROLL_CW)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(true));
        if (actionStatus == ACTION_ROLL_CCW)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(false));
        
        if (actionStatus == ACTION_YAW_CW)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(true));
        if (actionStatus == ACTION_YAW_CCW)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(false));
        
        if (actionStatus == ACTION_PITCH_UP)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(true));
        if (actionStatus == ACTION_PITCH_DOWN)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(false));
            
        spaceship.draw();
        // testing();

        // glLoadIdentity();
        // gluLookAt(0.0f, 0.0f, 10.0f,
        //           spaceship.x, 0.0f, 0.0f,
        //           0.0f, 1.0f, 0.0f);
        // glMultMatrixf(spaceship.rotationPosition.ptr());

        // other needy actions
        actionStatus = ACTION_NOTHING;
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
