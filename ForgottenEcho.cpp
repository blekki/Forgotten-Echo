#include <iostream>
#include <stdlib.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
// #include <glad/glad.h>

using namespace std;

//<><><> FUNCTIONS <><><>
//call actions if key pressed
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == 256 && action == 1){
        cout << "logs: window was closed" << endl;
        glfwSetWindowShouldClose(window, true);
    }
}

//<><><><><> MAIN PROGRAM <><><><><>
int main(void)
{
    //check does glfw run or not
    if (!glfwInit()){
        cout << "error: glfw can't run" << endl;
        exit(EXIT_FAILURE);
    }

    //time and fps
    // double time = glfwGetTime();
    glfwSwapInterval(1);

    //create window
    GLFWwindow* basicWindow = glfwCreateWindow(600, 400, "Basic Window", NULL, NULL);
    if (!basicWindow){
        cout << "error: window can't be created" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(basicWindow);

    //key enter function
    glfwSetKeyCallback(basicWindow, key_callback);

    //size of window
    int width {600};
    int height {400};
    glfwGetFramebufferSize(basicWindow, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //set coordinates system for window
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    //loop
    while(!glfwWindowShouldClose(basicWindow)){
        glClear(GL_COLOR_BUFFER_BIT);
        
        //created triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5, -0.5);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0, 0.5);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.5, -0.5);
        glEnd();

        //other needy actions
        glfwSwapBuffers(basicWindow);
        glfwPollEvents();
    }

    //close everything
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
