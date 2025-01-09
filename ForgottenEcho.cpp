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

GLuint loadShaider(string vertexSource, string fragmentSource){
    // ### vectex shader ###
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(vertexShader);
        cout << "infolog: " << (char*) infoLog.data() << endl;        
        return 0;
    }

    // ### fragment shader ###
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        cout << "infolog: " << (char*) infoLog.data() << endl;
        return 0;
    }

    // ### repeiring shader ###
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        cout << "infolog: " << (char*) infoLog.data() << endl;
        return 0;
    }

    // complite shader
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return program;
}

void drawCoord(float x, float y, float z, float *rotation){    
    float xPoint[3] {3, 0, 0};
    float yPoint[3] {0, 3, 0};
    float zPoint[3] {0, 0, 3};
    float *array[3] {xPoint, yPoint, zPoint};
    
    glPushMatrix();
    // replace axis
    glTranslatef(x, y, z);
    glMultMatrixf(rotation);
    // draw axis
    glLineWidth(3);
    glBegin(GL_LINES);
    for (int a = 0; a < 3; a++){
        glColor3fv(array[a]);
        glVertex3f(0, 0, 0); // zero point
        glVertex3fv(array[a]); //axis point
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

    GLuint spaceshipShader = loadShaider(
        R"cut(
            void main(){
                // gl_Vertex;

                // gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
                // gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
                gl_Position = ftransform();
            }
        )cut",
        R"cut(
            uniform float time;
            uniform vec2 dimensions;
            // bool colorType;

            void main(){
                // vec2  p = 7.*(2.*gl_FragCoord.xy-dimensions.xy)/dimensions.y;
                // float m1 = sin(length(p)*0.3-time*0.3);
                // float m2 = sin(0.3*(length(p)*0.3-time*0.3));
                // float c1 = 0.012/abs(length(mod(p,2.0*m1)-m1)-0.3);
                // float c2 = 0.012/abs(length(mod(p,2.0*m2)-m2)-0.3);
                // gl_FragColor = vec4(vec3(1.,2.,8.)*c1+vec3(8.,2.,1.)*c2, 1.);
                
                vec4 color;
                float g;
                g = mod(gl_FragCoord.x + gl_FragCoord.y, 2.0);
                color = vec4(g, g, g, 1.0);
                gl_FragColor = color;
            }
        )cut"
    );

    GLuint planetShader = loadShaider(
        R"cut(
            uniform sampler2D tex;
            varying vec2 st;
            void main(){
                gl_Position = ftransform();
                st = gl_MultiTexCoord0.st;
            }
        )cut",
        R"cut(
            uniform sampler2D tex;
            varying vec2 st;
            void main(){
                gl_FragColor = texture2D(tex, st);
            }
        )cut"
    );

    GLuint brightnestShader = loadShaider(
        R"cut(
            #version 120
            #define gl_ViewMatrix gl_ModelViewMatrix
            varying vec4 currentVertex;
            varying vec3 currentNormal;
            varying vec4 lightVertex;
            uniform vec4 lightPos;
            uniform mat4 modelMatrix;
            varying vec2 st;

            void main(){
                currentVertex = modelMatrix * gl_Vertex;
                currentNormal = mat3(modelMatrix) * gl_Normal;
                lightVertex = lightPos;


                // currentNormal = gl_Normal;
                // currentVertex = gl_Vertex.xyz;

                gl_Position = gl_ProjectionMatrix * gl_ViewMatrix * currentVertex;
                st = gl_MultiTexCoord0.st;
            }
        )cut",
        R"cut(
            varying vec4 currentVertex;
            varying vec3 currentNormal;
            varying vec4 lightVertex;
            
            uniform sampler2D tex;
            varying vec2 st;
            
            void main(){
                vec3 lightVec = normalize(lightVertex.xyz- currentVertex.xyz);
                vec3 normal = normalize(currentNormal);
        
                float result = max(dot(normal, lightVec), 0.1);

                vec3 color = vec3(result, result, result);
                gl_FragColor = texture2D(tex, st) * result;
            }
        )cut"
    );

    //enable gl functions
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);


    JsonReader jsonReader;
    // planets creating
    Planet mars;
    jsonReader.getPlanet(&mars, "characters/planets/mars.json");
    Planet moon;
    jsonReader.getPlanet(&moon, "characters/planets/moon.json");

    Object spaceship;
    jsonReader.getSpaceship(&spaceship, "characters/objects/myship.json");
    Object mothership;
    jsonReader.getSpaceship(&mothership, "characters/objects/mothership.json");
    Object testObj;
    jsonReader.getSpaceship(&testObj, "characters/objects/test.json");

    // prepering everything for rotationMatrices
    rotMatrices coupleMatrices;
    coupleMatrices.newMatrices();

    Primal primalObj;
    ParticleBox particle;
    particle.newGenerate();

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
        Vec3 whereIam {spaceship.position.x, spaceship.position.y, spaceship.position.z};
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
        drawCoord(spaceship.position.x, spaceship.position.y, spaceship.position.z, spaceship.rotationPosition.ptr());
        drawCoord(0, 0, 0, spaceship.rotationPosition.ptr());
        // drawing objects
        int tex = glGetUniformLocation(brightnestShader, "tex");
        int pos = glGetUniformLocation(brightnestShader, "lightPos");
        int matrix = glGetUniformLocation(brightnestShader, "modelMatrix");
        glUseProgram(brightnestShader);
        glUniform1i(tex, 0);
        glUniform4f(pos, sun.getX(), sun.getY(), sun.getZ(), 1);
        Matrix4 modelMatrix;
        // glUniform3f(pos, lightBox.getX(0), lightBox.getY(0), lightBox.getZ(0));
        sun.lightInit();
        sun.lightMat(spaceship.rotationPosition);
        // mars.draw();
        // moon.draw();
        // sun.draw();

        modelMatrix = mothership.makeModelMatrix();
        glUniformMatrix4fv(matrix, 1, false, modelMatrix.ptr());
        mothership.draw();
        
        modelMatrix = testObj.makeModelMatrix();
        glUniformMatrix4fv(matrix, 1, false, modelMatrix.ptr());
        testObj.draw();
        
        if (!firstPerson){
            spaceship.draw();
        }

        glUseProgram(0);
        
        // replace particalBox around your spaceship
        particle.newBoxPosition(spaceship.position.x, spaceship.position.y, spaceship.position.z);
        particle.draw();



        // a few actions for replace in space our spaceship and lightBox
        if (actionStatus & ACTION_ROLL_CCW)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(false));
        if (actionStatus & ACTION_ROLL_CW)
            spaceship.addRotateMatrix(coupleMatrices.getRoll(true));
        
        if (actionStatus & ACTION_YAW_CCW)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(false));
        if (actionStatus & ACTION_YAW_CW)
            spaceship.addRotateMatrix(coupleMatrices.getYaw(true));
        
        if (actionStatus & ACTION_PITCH_UP)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(false));
        if (actionStatus & ACTION_PITCH_DOWN)
            spaceship.addRotateMatrix(coupleMatrices.getPitch(true));
        
        if (actionStatus & ACTION_MOVE_BACK)
            spaceship.addTranslateVec(Vec3(0,0,1));
        if (actionStatus & ACTION_MOVE_FORWARD)
            spaceship.addTranslateVec(Vec3(0,0,-1));

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
