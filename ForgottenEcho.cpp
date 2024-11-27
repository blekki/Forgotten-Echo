#include <iostream>
#include <stdlib.h>
#include <cmath>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>
// #include <glad/glad.h>

using namespace std;

//<><><> NEEDY CONSTANTS
const float PiDiv180 = 3.1415f / 180.0f;
int textureID;
int sphere;

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
// coef for x coordinate
float coefX(float x)
{
    return (x / 1.5);
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

void normalize(float vec[]){
    float coef = 1.0f / (sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2)));
    vec[0] *= coef;
    vec[1] *= coef;
    vec[2] *= coef;
}

void vertex(float a[]){
    float x {a[0]};
    float y {a[1]};
    float z {a[2]};

    float phi = 1.0f - (1.0f + atan2(x, -z) / 3.14f) / 2.0f;
    float theta = acos(y) / 3.14f;

    glTexCoord2f(phi, theta);
    glVertex3fv(a);
}

void multiTriangle(float a[], float b[], float c[], int resolution){
    if(resolution > 0){
        float d[3] = {(a[0]+ b[0]) / 2.0f, (a[1]+ b[1]) / 2.0f, (a[2]+ b[2]) / 2};
        normalize(d);
        float e[3] = {(c[0]+ b[0]) / 2.0f, (c[1]+ b[1]) / 2.0f, (c[2]+ b[2]) / 2};
        normalize(e);
        float f[3] = {(a[0]+ c[0]) / 2.0f, (a[1]+ c[1]) / 2.0f, (a[2]+ c[2]) / 2};
        normalize(f);

        multiTriangle(a, d, f, resolution - 1);
        multiTriangle(f, e, c, resolution - 1);
        multiTriangle(d, b, e, resolution - 1);
        multiTriangle(d, f, e, resolution - 1);
    }
    else{
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(GL_TRIANGLES);
        float color = 1.0f; //fabs(1.0f * a[0]) + 0.1f;
        glColor3d(color, color, color);
        vertex(a);
        vertex(b);
        vertex(c);
        
        // glVertex3fv(b);
        // glVertex3fv(c);
        glEnd();
    }
}

void triangleSphere(int resolution){ //right now resolution = 1

    float angle60 = 6.28f / 3.0f;
    for(int i = 0; i < 3; i++){
        
        float a[3] {0.0f, cos(0.0f), 0.0f};
        float b[3] {cos(angle60 * i) * sin(angle60), cos(angle60), sin(angle60 * i) * sin(angle60)};
        float c[3] {cos(angle60 * (i + 1)) * sin(angle60), cos(angle60), sin(angle60 * (i + 1)) * sin(angle60)};
        
        multiTriangle(a, b, c, resolution);
    }
    float a[3] {sin(angle60), cos(angle60), 0.0f};
    float b[3] {cos(angle60) * sin(angle60), cos(angle60), sin(angle60) * sin(angle60)};
    float c[3] {cos(angle60 * 2) * sin(angle60), cos(angle60), sin(angle60 * 2) * sin(angle60)};
    multiTriangle(a, b, c, resolution);
}

//<><><><><> MAIN PROGRAM <><><><><>
int main(void)
{
    // check does glfw run or not
    if (!glfwInit())
    {
        cout << "error: glfw didn'd run" << endl;
        exit(EXIT_FAILURE);
    }

    // time and fps
    double time = glfwGetTime();
    glfwSwapInterval(1);

    int width{600};
    int height{400};

    // create window
    GLFWwindow *basicWindow = glfwCreateWindow(width, height, "Basic Window", NULL, NULL);
    if (!basicWindow)
    {
        cout << "error: window can't be created" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(basicWindow);
    textureID = SOIL_load_OGL_texture("./solarsystemscope/2k_moon.jpg", SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    cout << "texture: " << textureID << endl;

    //enable gl functions
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    // key enter function
    glfwSetKeyCallback(basicWindow, key_callback);

    // size of window
    glfwGetFramebufferSize(basicWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // set coordinates system for window
    glLoadIdentity();
    glOrtho(-((float)width / (float)height), ((float)width / (float)height), -1, 1, -1, 1);

    // loop
    float angle = 0.0f;
    while (!glfwWindowShouldClose(basicWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // createCircle(0.0f, 0.0f, 1.0f);
        // createTriangle();
        // createSphere(100);
        if (sphere == 0){
            sphere = glGenLists(1);
            glNewList(sphere, GL_COMPILE);
            triangleSphere(4);
            glEndList();
        }
        glCallList(sphere);

        // rotate object and change that position
        //  glTranslated(cos(angle) / 100.0f, 0.0f, 0.0f);
        //  angle += 0.01;
        glRotated(1.0f, 1.0f, 1.0f, 0.0f);
        

        // other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    // close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
