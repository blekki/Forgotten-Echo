#include <iostream>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "sphere.h"

//normalize 3-component vector (up to 1.0f)
void normalize(float vec[]){
    float coef = 1.0f / (sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2)));
    vec[0] *= coef;
    vec[1] *= coef;
    vec[2] *= coef;
}

//draw a triangle with texture
void Sphere::vertex(float a[]){
    glVertex3fv(a);
}

//divide one triangle into four some smaller
void Sphere::multiTriangle(float a[], float b[], float c[], int resolution){
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
        //generate triangles
        vertex(a);
        vertex(b);
        vertex(c);
    }
}

//function for creating icosphere
void Sphere::triangleSphere(int resolution){ //right now resolution = 1
    glBegin(GL_TRIANGLES);

    float angle60 = 6.283f / 3.0f;
    for(int i = 0; i < 3; i++){
        float a[3] {0.0f, cos(0.0f), 0.0f};
        float b[3] {cosf(angle60 * i) * sinf(angle60), cosf(angle60), sinf(angle60 * i) * sinf(angle60)};
        float c[3] {cosf(angle60 * (i + 1.0f)) * sinf(angle60), cosf(angle60), sinf(angle60 * (i + 1.0f)) * sinf(angle60)};
        multiTriangle(a, b, c, resolution);
    }
    float a[3] {sinf(angle60), cosf(angle60), 0.0f};
    float b[3] {cosf(angle60) * sinf(angle60), cosf(angle60), sinf(angle60) * sinf(angle60)};
    float c[3] {cosf(angle60 * 2.0f) * sinf(angle60), cosf(angle60), sinf(angle60 * 2.0f) * sinf(angle60)};
    multiTriangle(a, b, c, resolution);

    glEnd();
}