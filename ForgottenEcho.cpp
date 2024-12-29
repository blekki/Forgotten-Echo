#include <iostream>
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
        firstPerson = 1;
    if (key == GLFW_KEY_2)
        firstPerson = 0;

}

GLuint loadShaider(string vertexSource, string fragmentSource){
    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        
        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        cout << "infolog: " << (char*) infoLog.data() << endl;
        
        // In this simple program, we'll just leave
        return 0;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        
        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        cout << "infolog: " << (char*) infoLog.data() << endl;
        
        // In this simple program, we'll just leave
        return 0;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        
        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.
        cout << "infolog: " << (char*) infoLog.data() << endl;
        // In this simple program, we'll just leave
        return 0;
    }

    // Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    return program;
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
    cout << glGetString(GL_VENDOR) << endl;
    cout << glGetString(GL_VERSION) << endl;
    if (glewInit()) {
        cout << "error: glew didn't run" << endl;
        exit(EXIT_FAILURE);
    }
    // cout << glGetString(GL_EXTENSIONS) << endl;
    if (!strstr((const char*) glGetString(GL_EXTENSIONS), "GL_ARB_texture_non_power_of_two")){
        cout << "у вас немає розширення" << endl;
        exit(EXIT_FAILURE);
    }

    GLuint program = loadShaider(
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
            void main(){
                vec2  p = 7.*(2.*gl_FragCoord.xy-dimensions.xy)/dimensions.y;
                float m1 = sin(length(p)*0.3-time*0.3);
                float m2 = sin(0.3*(length(p)*0.3-time*0.3));
                float c1 = 0.012/abs(length(mod(p,2.0*m1)-m1)-0.3);
                float c2 = 0.012/abs(length(mod(p,2.0*m2)-m2)-0.3);
                gl_FragColor = vec4(vec3(1.,2.,8.)*c1+vec3(8.,2.,1.)*c2, 1.);
            }
        )cut"
    );

    GLuint program2 = loadShaider(
        R"cut(
            uniform sampler2D tex;
            // varying vec2 st;
            varying vec4 color;
            void main(){
                gl_Position = ftransform();
                color = texture2D(tex, st);
                st = gl_MultiTexCoord0;
            }
        )cut",
        R"cut(
            uniform sampler2D tex;
            varying vec2 st;
            varying vec4 color;
            void main(){
                // gl_FragColor = color;
                gl_FragColor = texture2D(tex, st);
            }
        )cut"
    );

    //enable gl functions
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);

    //planets creating
    Planet mars;
    mars.setTexture("solarsystemscope/2k_mars.jpg");
    mars.setScale(100.0f);
    mars.setPosition(0.0f, 0.0f, -400.0f);
    mars.setRotateSpeed(1.5f);

    Planet moon;
    moon.setTexture("solarsystemscope/2k_moon.jpg");
    moon.setScale(15.0f);
    moon.setPosition(50.0f, -30.0f, -300.0f);
    moon.setRotateSpeed(-2.0f);

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
        drawCoord(spaceship.position.x, spaceship.position.y, spaceship.position.z, spaceship.rotationPosition.ptr(), true);
        drawCoord(0, 0, 0, spaceship.rotationPosition.ptr(), false);
        // drawing objects
        int tex = glGetUniformLocation(program2, "tex");
        glUseProgram(program2);
        glUniform1i(tex, 0);
        mars.draw();
        moon.draw();
        glUseProgram(0);
        if (!firstPerson){
            int time = glGetUniformLocation(program, "time");
            int dimensions = glGetUniformLocation(program, "dimensions");
            glUseProgram(program);
            glUniform1f(time, glfwGetTime());
            glUniform2f(dimensions, width, height);
            spaceship.draw();
            glUseProgram(0);
        }
        
        // particle.setBoxPosition(spaceship.x, spaceship.y, glfwGetTime() * 0.9f);
        particle.newBoxPosition(spaceship.position.x, spaceship.position.y, spaceship.position.z);
        particle.draw();



        // a few actions for rotation an our object
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
