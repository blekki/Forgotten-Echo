#include <iostream>
#include <stdlib.h>
#include <GLFW/glfw3.h>

using namespace std;

//<><><> FUNCTIONS <><><>
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == 256 && action == 1){
        cout << "logs: window was closed" << endl;
        glfwSetWindowShouldClose(window, true);
    }
}

//<><><><><> main programm <><><><><>
int main(void)
{
    //check does glfw run or not
    if (!glfwInit()){
        cout << "[ERROR] glfw can't run" << endl;
        exit(EXIT_FAILURE);
    }

    //create window
    GLFWwindow* basicWindow = glfwCreateWindow(600, 400, "Basic Window", NULL, NULL);
    if (!basicWindow){
        cout << "[error] window can't be created" << endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(basicWindow);

    glfwSetKeyCallback(basicWindow, key_callback);

    //loop
    while(!glfwWindowShouldClose(basicWindow)){
        glfwPollEvents();
    }

    
    glfwDestroyWindow(basicWindow);
    glfwTerminate();
}
