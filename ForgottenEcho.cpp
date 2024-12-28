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
    ACTION_NOTHING = 0,

    ACTION_ROLL_CW = 1,
    ACTION_ROLL_CCW = 2,
    ACTION_YAW_CW = 4,
    ACTION_YAW_CCW = 8,
    ACTION_PITCH_UP = 16,
    ACTION_PITCH_DOWN = 32,

    ACTION_MOVE_FORWARD = 64,
    ACTION_MOVE_BACK = 128,
};

int actionStatus = ACTION_NOTHING;
int firstPerson = 1;

//<><><> FUNCTIONS <><><>
void keyAction(string logs, action_t actionType, bool pressed){
    if (pressed){
        actionStatus |= actionType;
    }
    else actionStatus &= ~actionType;

    cout << logs << " - actionType " << actionType << " - actionStatus " << actionStatus << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) // call actions if key pressed
{
    //close application
    if (key == GLFW_KEY_ESCAPE && action == 1) {
        cout << "action: window was closed" << endl;
        glfwSetWindowShouldClose(window, true);
    }

    //###### rotate keys ######
    //keys right and left
    if (key == GLFW_KEY_Q)
        keyAction("action: key Q", ACTION_ROLL_CW, (action == 1 || action == 2));
    if (key == GLFW_KEY_E)
        keyAction("action: key E", ACTION_ROLL_CCW, (action == 1 || action == 2));

    //keys up and down
    if (key == GLFW_KEY_LEFT)
        keyAction("action: key left", ACTION_YAW_CW, (action == 1 || action == 2));
    if (key == GLFW_KEY_RIGHT)
        keyAction("action: key right", ACTION_YAW_CCW, (action == 1 || action == 2));

    //keys E and Q
    if (key == GLFW_KEY_UP)
        keyAction("action: key up", ACTION_PITCH_UP, (action == 1 || action == 2));
    if (key == GLFW_KEY_DOWN)
        keyAction("action: key down", ACTION_PITCH_DOWN, (action == 1 || action == 2));

    //###### move keys ######
    //keys W and S
    if (key == GLFW_KEY_W)
        keyAction("action: key W", ACTION_MOVE_FORWARD, (action == 1 || action == 2));
    if (key == GLFW_KEY_S)
        keyAction("action: key S", ACTION_MOVE_BACK, (action == 1 || action == 2));

    //###### view type ######
    if (key == GLFW_KEY_1)
        firstPerson = 0;
    if (key == GLFW_KEY_2)
        firstPerson = 1;

}

void drawCoord(float x, float y, float z, float *rotation, bool follow){
    
    float xPoint[3] {3, 0, 0};
    float yPoint[3] {0, 3, 0};
    float zPoint[3] {0, 0, 3};
    float *array[3] {xPoint, yPoint, zPoint};
    
    glPushMatrix();
    (follow) ? glTranslatef(x, y, z) : glTranslatef(0, 0, -2); //does exis follow ship or not
    glMultMatrixf(rotation);
    // draw exis
    glLineWidth(3);
    glBegin(GL_LINES);
    for (int a = 0; a < 3; a++){
        glColor3fv(array[a]);
        //#######
        glVertex3f(0, 0, 0);
        glVertex3fv(array[a]);
    }
    glEnd();
    glPopMatrix();
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

    //planets creating
    Planet mars;
    mars.setTexture("solarsystemscope/2k_mars.jpg");
    mars.setScale(60.0f);
    mars.setPosition(0.0f, 0.0f, -200.0f);
    mars.setRotateSpeed(20.0f);

    Planet moon;
    moon.setTexture("solarsystemscope/2k_moon.jpg");
    moon.setScale(8.0f);
    moon.setPosition(50.0f, -10.0f, -100.0f);
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

        // basic matrixes
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, width / (float) height, 0.1f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
        
        // follow for spaceship
        Vec3 whereIam {spaceship.x, spaceship.y, spaceship.z};
        Vec3 forward = multiplyMatrixVec(spaceship.rotationPosition, Vec3 {0, 0, -1});
        Vec3 to = whereIam + forward;
        Vec3 preUp = multiplyMatrixVec(spaceship.rotationPosition, Vec3 {0, 1, 0});
        if (firstPerson == 1){
            glLoadIdentity();
            gluLookAt(whereIam.x, whereIam.y, whereIam.z,
                      to.x, to.y, to.z,
                      preUp.x, preUp.y, preUp.z);
        }
        else{
            glLoadIdentity();
            gluLookAt(50, 0, 0,
                      to.x, to.y, to.z,
                      0, 1, 0);
        }

        // drawing axis
        drawCoord(spaceship.x, spaceship.y, spaceship.z, spaceship.rotationPosition.ptr(), true);
        drawCoord(0, 0, 0, spaceship.rotationPosition.ptr(), false);
        // drawing objects
        mars.draw();
        moon.draw();
        if (!firstPerson)
            spaceship.draw();

        // a few actions for rotation an our object
        if (actionStatus & ACTION_ROLL_CCW)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(true));
        if (actionStatus & ACTION_ROLL_CW)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(false));
        
        if (actionStatus & ACTION_YAW_CCW)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(true));
        if (actionStatus & ACTION_YAW_CW)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(false));
        
        if (actionStatus & ACTION_PITCH_UP)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(true));
        if (actionStatus & ACTION_PITCH_DOWN)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(false));
        
        if (actionStatus & ACTION_MOVE_BACK)
            spaceship.addTranslateVec(Vec3(0,0,1));
        if (actionStatus & ACTION_MOVE_FORWARD)
            spaceship.addTranslateVec(Vec3(0,0,-1));

        // glMultMatrixf(spaceship.rotationPosition.ptr());
        // spaceship.draw();
       

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
