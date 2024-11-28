#include <iostream>
#include <stdlib.h>
#include <cmath>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>

extern int textureID;

//normalize 3-component vector (up to 1.0f)
void normalize(float vec[]){
    float coef = 1.0f / (sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2)));
    vec[0] *= coef;
    vec[1] *= coef;
    vec[2] *= coef;
}

//draw a triangle with texture
void vertex(float a[]){
    float x {a[0]};
    float y {a[1]};
    float z {a[2]};

    float phi = 1.0f - (1.0f + atan2(x, -z) / 3.1415f) / 2.0f;
    float theta = acos(y) / 3.1415f;

    glTexCoord2f(phi, theta);
    glVertex3fv(a);
}

//divide one triangle into four some smaller
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
        //draw triangle
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(GL_TRIANGLES);
        glColor3d(1.0f, 1.0f, 1.0f);
        vertex(a);
        vertex(b);
        vertex(c);
        glEnd();
    }
}

//function for creating icosphere
void triangleSphere(int resolution){ //right now resolution = 1

    float angle60 = 6.283f / 3.0f;
    for(int i = 0; i < 3; i++){
        
        float a[3] {0.0f, cos(0.0f), 0.0f};
        float b[3] {cos(angle60 * i) * sin(angle60), cos(angle60), sin(angle60 * i) * sin(angle60)};
        float c[3] {cos(angle60 * (i + 1.0f)) * sin(angle60), cos(angle60), sin(angle60 * (i + 1.0f)) * sin(angle60)};
        
        multiTriangle(a, b, c, resolution);
    }
    float a[3] {sin(angle60), cos(angle60), 0.0f};
    float b[3] {cos(angle60) * sin(angle60), cos(angle60), sin(angle60) * sin(angle60)};
    float c[3] {cos(angle60 * 2.0f) * sin(angle60), cos(angle60), sin(angle60 * 2.0f) * sin(angle60)};
    multiTriangle(a, b, c, resolution);
}