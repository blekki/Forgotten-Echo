#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <cstring>
// #define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include <GL/glu.h>
// #include <glad/glad.h>
#include "Newton.h"
// everything for soundtracks
#include <AL/al.h>
#include <AL/alc.h>
#include <opus/opusfile.h>
#include <sched.h>

#include "ForgottenEcho.h"

// #include "primal.h"
// #include "sphere.h"
// #include "planet.h"
// #include "model.h"
// #include "object.h"
// #include "particlebox.h"
// #include "jsonReader.h"
// #include "entity.h"
// #include "spaceship.h"
// #include "sun.h"
#include "marsLocation.h"
#include "shopstate.h"

#include "cursor.h"
#include "soundtrack.h"
#include "shader/sunShader.h"



using namespace std;

//<><><> NEEDY CONSTANTS AND VARYABLES
int screen_width {600};
int screen_height {400};
int level = 0;
NewtonWorld *world;
Cursor *cursorP;

int actionStatus = ACTION_HANDING;
int personView = 1;
bool mute = true;

//<><><> FUNCTIONS <><><>
void keyAction(string logs, action_t actionType, bool pressed){
    if (pressed){
        actionStatus |= actionType;
    }
    else actionStatus &= ~actionType;

    // cout << logs << " - actionType " << actionType << " - actionStatus " << actionStatus << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) // call actions if key pressed
{
    //close application
    if (key == GLFW_KEY_ESCAPE && action == 1) {
        if (level != 1){
        cout << "action: window was closed" << endl;
        glfwSetWindowShouldClose(window, true);
        }
        else level = 0;
    }

    //###### keys for rotation ######
    //keys E and Q
    if (key == GLFW_KEY_Q)
        keyAction("action: key Q", ACTION_ROLL_CW, (action == 1 || action == 2));
    if (key == GLFW_KEY_E)
        keyAction("action: key E", ACTION_ROLL_CCW, (action == 1 || action == 2));

    //keys right and left
    if (key == GLFW_KEY_LEFT)
        keyAction("action: key left", ACTION_YAW_CW, (action == 1 || action == 2));
    if (key == GLFW_KEY_RIGHT)
        keyAction("action: key right", ACTION_YAW_CCW, (action == 1 || action == 2));

    //keys up and down
    if (key == GLFW_KEY_UP)
        keyAction("action: key up", ACTION_PITCH_UP, (action == 1 || action == 2));
    if (key == GLFW_KEY_DOWN)
        keyAction("action: key down", ACTION_PITCH_DOWN, (action == 1 || action == 2));

    //###### keys for movement ######
    //keys W and S
    if (key == GLFW_KEY_W)
        keyAction("action: key W", ACTION_MOVE_FORWARD, (action == 1 || action == 2));
    if (key == GLFW_KEY_S)
        keyAction("action: key S", ACTION_MOVE_BACK, (action == 1 || action == 2));

    //keys A and D
    if (key == GLFW_KEY_A)
        keyAction("action: key A", ACTION_MOVE_LEFT, (action == 1 || action == 2));
    if (key == GLFW_KEY_D)
        keyAction("action: key D", ACTION_MOVE_RIGHT, (action == 1 || action == 2));

    //keys space and shift
    if (key == GLFW_KEY_SPACE)
        keyAction("action: key space", ACTION_MOVE_UP, (action == 1 || action == 2));
    if (key == GLFW_KEY_LEFT_CONTROL)
        keyAction("action: key left ctrl", ACTION_MOVE_DOWN, (action == 1 || action == 2));

    if (key == GLFW_KEY_H && (action == 1)) {
        if (actionStatus & ACTION_HANDING) {
            actionStatus &= ~ACTION_HANDING;
        }
        else actionStatus |= ACTION_HANDING;
    }

    //###### view type ######
    if (key == GLFW_KEY_1 && (action == 1))
        personView = 1;
    if (key == GLFW_KEY_2 && (action == 1))
        personView = 0;
    
    //###### mute musik ######
    if (key == GLFW_KEY_M && (action == 1)){
        mute = (mute) ? false : true;
        cout << "mute:" << mute << endl;
    }

    if (key == GLFW_KEY_N && (action == 1)){ // todo: remove
        level = (level) ? 0 : 1;
        cout << "level:" << mute << endl;
    }

}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT && (action == 1)){
        // cout << "it was pushed" << endl;
        cursorP->printXY();
    }
}

static void cursor_position_callback(GLFWwindow *window, double x, double y){
    glfwGetCursorPos(window, &x, &y);
    cursorP->setX(x);
    cursorP->setY(y);
}

//##############################################
//<><><><><><><><> MAIN PROGRAM <><><><><><><><>
int main(void)
{   
    // prepare to using Newton library
    world = NewtonCreate();
    int newtonVersion = NewtonWorldGetVersion();
    cout << "NewtonVersion: " << newtonVersion / 100 << "." << newtonVersion % 100 << endl;
    NewtonSetSolverIterations(world, 1);

    ALCdevice *dev = alcOpenDevice(NULL);
    ALCcontext *ctx = alcCreateContext(dev, NULL);
    alcMakeContextCurrent(ctx);
    cout << "openAL version: " << alGetString(AL_VERSION) << endl;
    cout << "openAL vendor: " << alGetString(AL_VENDOR) << endl;
    cout << "openAL renderer: " << alGetString(AL_RENDERER) << endl;

    // check did glfw run or not
    if (!glfwInit()) {
        cout << "error: glfw didn't run" << endl;
        exit(EXIT_FAILURE);
    }
    glfwSetTime(0.0f); // set basic position to the time

    // create window
    GLFWwindow *basicWindow = glfwCreateWindow(screen_width, screen_height, "Basic Window", NULL, NULL);
    if (!basicWindow) {
        cout << "error: window can't be created" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(basicWindow);
    // preparation for custom shader
    cout << "GL_VENDOR :" << glGetString(GL_VENDOR) << endl;
    cout << "GL_VERSION : " << glGetString(GL_VERSION) << endl;
    if (glewInit()) {
        cout << "error: glew didn't run" << endl;
        exit(EXIT_FAILURE);
    }
    if (!strstr((const char*) glGetString(GL_EXTENSIONS), "GL_ARB_texture_non_power_of_two")){
        cout << "You haven't needy extension for glew" << endl;
        exit(EXIT_FAILURE);
    }

    // GLuint spaceshipShader = loadShaider(
    //     R"cut(
    //         void main(){
    //             // gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    //             gl_Position = ftransform();
    //         }
    //     )cut",
    //     R"cut(
    //         uniform float time;
    //         uniform vec2 dimensions;

    //         void main(){
    //             vec2  p = 7.*(2.*gl_FragCoord.xy-dimensions.xy)/dimensions.y;
    //             float m1 = sin(length(p)*0.3-time*0.3);
    //             float m2 = sin(0.3*(length(p)*0.3-time*0.3));
    //             float c1 = 0.012/abs(length(mod(p,2.0*m1)-m1)-0.3);
    //             float c2 = 0.012/abs(length(mod(p,2.0*m2)-m2)-0.3);
    //             gl_FragColor = vec4(vec3(1.,2.,8.)*c1+vec3(8.,2.,1.)*c2, 1.);
    //         }
    //     )cut"
    // );

    // enable gl functions
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);
    glfwSetMouseButtonCallback(basicWindow, mouse_button_callback);
    glfwSetCursorPosCallback(basicWindow, cursor_position_callback);


    MarsLocation marsLocation;
    marsLocation.pushWindowLink(basicWindow);
    Shopstate shopstate;

    Soundtrack soundtrack;
    soundtrack.loadSound("media/ObservingTheStar.opus");
    soundtrack.play();


    cursorP = marsLocation.getCursorPtr();


    float time = glfwGetTime();
    // loop
    while (!glfwWindowShouldClose(basicWindow))
    {   
        sched_yield();

        //Newton dynamic calculation -------------------  : 3d state
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - time;
        time = currentTime;
        NewtonUpdate(world, deltaTime);
        
        // musik part
        alSourcef(soundtrack.getSource(), AL_GAIN, mute);
        // alSourcei(soundtrack.getSource(), AL_LOOPING, 1);
        

        // ------ prepareGamestate
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //prerender pass --------------------------------
        switch (level) {
        case 0: marsLocation.prerender();
            break;
        case 1: shopstate.prerender();
            break;
        default:
            break;
        }

        //render pass -----------------------------------

        // size of window : void state/level
        glfwGetFramebufferSize(basicWindow, &screen_width, &screen_height);
        glViewport(0, 0, screen_width, screen_height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

        switch (level) {
        case 0: 
            {
                marsLocation.prepareMatrix();
                marsLocation.pushPersonView(personView);
                marsLocation.newActionStatus(actionStatus);
                marsLocation.render();        
            }
            break;
        case 1:
            shopstate.render();
            break;
        default:
            break;
        }

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();

    NewtonDestroy(world);
}
