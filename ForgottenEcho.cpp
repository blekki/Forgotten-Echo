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

#include "soundtrack.h"
#include "shader/sunShader.h"



using namespace std;

//<><><> NEEDY CONSTANTS AND VARYABLES
int screen_width{600};
int screen_height{400};

NewtonWorld *world;

int actionStatus = ACTION_NOTHING;
int firstPerson = 1;
int mute = 1;

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
        cout << "action: window was closed" << endl;
        glfwSetWindowShouldClose(window, true);
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

    //###### view type ######
    if (key == GLFW_KEY_1 && (action == 1))
        firstPerson = 1;
    if (key == GLFW_KEY_2 && (action == 1))
        firstPerson = 0;
    
    if (key == GLFW_KEY_M && (action == 1)){
        mute = (mute) ? false : true;
        cout << "mute:" << mute << endl;
    }

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

    // ALuint alBuffers;
    // ALuint alSources;
    // alGenBuffers(1, &alBuffers);
    // alGenSources(1, &alSources);
    
    // alListener3f(AL_POSITION, 0, 0, 0);
    // alListenerf(AL_GAIN, 1);
    // int ok;
    // auto file = op_open_file("media/ObservingTheStar.opus", &ok);
    // if (ok != 0) {
    //     cout << "opus file not readed" << endl;
    //     return 0;
    // }

    // int channels = op_channel_count(file, -1);
    // int pcm_size = op_pcm_total(file, -1);
    // cout << "sound channels: " << channels << endl;
    // cout << "sound pcm_size: " << pcm_size << endl;
    // cout << "sound length (sec): " << pcm_size / 48000 << endl;

    // short* buf = (short *) malloc(pcm_size * channels * sizeof(short));
    // int ns = 0;
    // int oldNs = ns;
    // while (oldNs < pcm_size - 1) {
    //     ns = op_read(file, &buf[oldNs * channels], pcm_size - oldNs, NULL);
    //     if (ns == -1) return 10;
    //     oldNs += ns;
    // }

    // op_free(file);

    // alBufferData(alBuffers, AL_FORMAT_STEREO16, buf, pcm_size * channels * sizeof(short), 48000);
    // alSourcei(alSources, AL_BUFFER, alBuffers);
    // alSource3f(alSources, AL_POSITION, 0, 0, 0);
    // alSourcef(alSources, AL_GAIN, 1);

    // alSourcePlay(alSources);

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
    sun.screen_width = screen_width; //todo: remove/make simpler
    sun.screen_height = screen_height;

    Spaceship spaceship;
    jsonReader.readJsonSpaceship(&spaceship, "characters/objects/myship.json");
    spaceship.setControlStatus(true);
    Spaceship mothership;
    jsonReader.readJsonSpaceship(&mothership, "characters/objects/mothership.json");
    Spaceship testObj;
    jsonReader.readJsonSpaceship(&testObj, "characters/objects/test.json");

    ParticleBox particle;
    particle.newGenerate();

    Soundtrack soundtrack;
    soundtrack.loadSound("media/ObservingTheStar.opus");
    soundtrack.play();

    // shader preparation
    Brightness brightnessShader;
    PlanetShader planetShader;
    SunShader sunShader;

    float time = glfwGetTime();
    bool ggg = true;
    // loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(basicWindow))
    {
        sched_yield();

        //Newton dynamic calculation -------------------
        float currentTime = glfwGetTime();
        float delta = currentTime - time;
        time = currentTime;
        NewtonUpdate(world, delta);

        // int deltaPlus = (int) (glfwGetTime() * 1000);
        // alSource3f(alSources, AL_POSITION, cos(glfwGetTime()) * 8.0f, 0, sin(glfwGetTime()) * 8.0f);
        // soundtrack.play();
        alSourcef(soundtrack.getSource(), AL_GAIN, mute);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //prerender pass --------------------------------
        sun.prerender(sunShader);
        //render pass -----------------------------------

        // size of window
        glfwGetFramebufferSize(basicWindow, &screen_width, &screen_height);
        glViewport(0, 0, screen_width, screen_height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

        // basic matrixes
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(65.0f, screen_width / (float) screen_height, 0.1f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
        
        // follow for spaceship
        Vec3 whereIam {spaceship.getX(), spaceship.getY(), spaceship.getZ()};
        Vec3 forward = multiplyMatrixVec(spaceship.makeModelMatrix(), Vec3 {0, 0, -1});
        Vec3 to = whereIam + forward;
        Vec3 preUp = multiplyMatrixVec(spaceship.makeModelMatrix(), Vec3 {0, 1, 0});
        if (firstPerson == 1){
            glLoadIdentity();
            gluLookAt(whereIam.x, whereIam.y, whereIam.z,
                      to.x, to.y, to.z,
                      preUp.x, preUp.y, preUp.z);
        }
        else{
            glLoadIdentity();
            gluLookAt(50, 0, 0,
                      spaceship.getX(), spaceship.getY(), spaceship.getZ(),
                      0, 1, 0);
        }

        // draw objects (and spaceships)
        glUseProgram(brightnessShader.getShaderID());
        brightnessShader.setSun(sun.getXYZ());
        mothership.draw(brightnessShader);
        testObj.draw(brightnessShader);

        spaceship.pushActionStatus(actionStatus);
        if (!firstPerson){
            spaceship.draw(brightnessShader);
        }

        // draw planets
        glUseProgram(planetShader.getShaderID());
        planetShader.setSun(sun.getXYZ());
        mars.draw(planetShader, spaceship.getXYZ());
        moon.draw(planetShader, spaceship.getXYZ());
        mercury.draw(planetShader, spaceship.getXYZ());
        glUseProgram(0);

        sun.draw(spaceship.getXYZ());
        // glViewport(0, 0, screen_width, screen_height);
        
        // replace particalBox around your spaceship
        particle.newBoxPosition(spaceship.getX(), spaceship.getY(), spaceship.getZ());
        particle.draw();

        // drawing axis
        primal.drawFollowCoord(spaceship.makeModelMatrix());
        primal.drawCoord();

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();

    NewtonDestroy(world);
}
