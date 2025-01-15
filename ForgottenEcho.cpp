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

#include "primal.h"
#include "sphere.h"
#include "planet.h"
#include "model.h"
#include "object.h"
#include "particlebox.h"
#include "jsonReader.h"
#include "entity.h"
#include "spaceship.h"
#include "sun.h"

#include "shader/sunShader.h"


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

    //###### move keys ######
    //keys W and S
    if (key == GLFW_KEY_W)
        keyAction("action: key W", ACTION_MOVE_FORWARD, (action == 1 || action == 2));
    if (key == GLFW_KEY_S)
        keyAction("action: key S", ACTION_MOVE_BACK, (action == 1 || action == 2));

    //###### view type ######
    if (key == GLFW_KEY_1)
        firstPerson = 1;
    if (key == GLFW_KEY_2)
        firstPerson = 0;

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
    //             // gl_Vertex;

    //             // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //             // gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    //             gl_Position = ftransform();
    //         }
    //     )cut",
    //     R"cut(
    //         uniform float time;
    //         uniform vec2 dimensions;
    //         // bool colorType;

    //         void main(){
    //             // vec2  p = 7.*(2.*gl_FragCoord.xy-dimensions.xy)/dimensions.y;
    //             // float m1 = sin(length(p)*0.3-time*0.3);
    //             // float m2 = sin(0.3*(length(p)*0.3-time*0.3));
    //             // float c1 = 0.012/abs(length(mod(p,2.0*m1)-m1)-0.3);
    //             // float c2 = 0.012/abs(length(mod(p,2.0*m2)-m2)-0.3);
    //             // gl_FragColor = vec4(vec3(1.,2.,8.)*c1+vec3(8.,2.,1.)*c2, 1.);
                
    //             vec4 color;
    //             float g;
    //             g = mod(gl_FragCoord.x + gl_FragCoord.y, 2.0);
    //             color = vec4(g, g, g, 1.0);
    //             gl_FragColor = color;
    //         }
    //     )cut"
    // );

    //enable gl functions
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);


    JsonReader jsonReader;
    Primal primal;
    // planets creating
    Planet mars;
    jsonReader.readJsonPlanet(&mars, "characters/planets/mars.json");
    Planet moon;
    jsonReader.readJsonPlanet(&moon, "characters/planets/moon.json");
    Planet mercury;
    jsonReader.readJsonPlanet(&mercury, "characters/planets/mercury.json");
    Sun sun;
    jsonReader.readJsonSun(&sun, "characters/planets/sun.json");

    Spaceship spaceship;
    jsonReader.readJsonSpaceship(&spaceship, "characters/objects/myship.json");
    Spaceship mothership;
    jsonReader.readJsonSpaceship(&mothership, "characters/objects/mothership.json");
    Spaceship testObj;
    jsonReader.readJsonSpaceship(&testObj, "characters/objects/test.json");

    Primal primalObj;
    ParticleBox particle;
    particle.newGenerate();

    Brightness brightnessShader;
    PlanetShader planetShader;
    SunShader sunShader;
    // sunShader.SunShader2();

    GLuint coronaTexture;
    glGenTextures(1, &coronaTexture);
    glBindTexture(GL_TEXTURE_2D, coronaTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, coronaTexture, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(basicWindow))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glViewport(0, 0, 256, 256);
        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glUseProgram(sunShader.getShaderID());
        sunShader.setTime(glfwGetTime() / 10.0f);
        glBegin(GL_QUADS);
        glVertex2f(-1, -1);
        glVertex2f(-1,  1);
        glVertex2f( 1,  1);
        glVertex2f( 1, -1);
        glEnd();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);


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
        Vec3 whereIam {spaceship.getX(), spaceship.getY(), spaceship.getZ()};
        Vec3 forward = multiplyMatrixVec(spaceship.getRotation(), Vec3 {0, 0, -1});
        Vec3 to = whereIam + forward;
        Vec3 preUp = multiplyMatrixVec(spaceship.getRotation(), Vec3 {0, 1, 0});
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

        // draw objects (spaceships)
        glUseProgram(brightnessShader.getShaderID());
        brightnessShader.setSun(sun.getXYZ());
        mothership.draw(brightnessShader);
        testObj.draw(brightnessShader);
        if (!firstPerson){
            spaceship.draw(brightnessShader);
        }

        // draw planets
        glUseProgram(planetShader.getShaderID());
        planetShader.setSun(sun.getXYZ());
        mars.draw(planetShader);
        moon.draw(planetShader);
        mercury.draw(planetShader);
        glUseProgram(0);

        // draw sun dynamic texture
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, coronaTexture);
        glEnable(GL_TEXTURE_2D);
        sun.draw();
        glBindTexture(GL_TEXTURE_2D, 0);
        glBlendFunc(GL_ONE, GL_ZERO);

        glUseProgram(0);
        // replace particalBox around your spaceship
        particle.newBoxPosition(spaceship.getX(), spaceship.getY(), spaceship.getZ());
        particle.draw();

        // drawing axis
        primal.drawFollowCoord(spaceship.getX(), spaceship.getY(), spaceship.getZ(), spaceship.getRotation().ptr());
        primal.drawCoord();



        // a few actions for replace in space our spaceship and lightBox
        if (actionStatus & ACTION_ROLL_CCW)
            spaceship.roll(false);
        if (actionStatus & ACTION_ROLL_CW)
            spaceship.roll(true);
        
        if (actionStatus & ACTION_YAW_CCW)
            spaceship.yaw(false);
        if (actionStatus & ACTION_YAW_CW)
            spaceship.yaw(true);
        
        if (actionStatus & ACTION_PITCH_UP)
            spaceship.pitch(false);
        if (actionStatus & ACTION_PITCH_DOWN)
            spaceship.pitch(true);
        
        if (actionStatus & ACTION_MOVE_BACK)
            spaceship.shift(0, 0, 1);
        if (actionStatus & ACTION_MOVE_FORWARD)
            spaceship.shift(0, 0, -1);

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
