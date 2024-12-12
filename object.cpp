#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

#include "object.h"

using namespace std;

//set basic object characteristics
void Object::setPosition(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Object::setRotate(float angleX){
    this->angleX = angleX;
    // this->angleY = angleY;
}

void Object::setScale(float scale){
    this->scale = scale;
}

//draw object on screen
void Object::drawTriangles(){
    const int TRIANGLE_VERTICES = 3;

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    int meshCount = this->geometry.size();
    for (int m = 0; m < meshCount; m++) { //read every mesh with triangles
        glBindTexture(GL_TEXTURE_2D, this->materialList.at(m).textureID);
        // cout << "textureID: " << this->materialList.at(m).textureID << endl;

        int triangleCount = this->geometry.at(m)->triangles.size();
        for (int tr = 0; tr < triangleCount; tr++) { //read every triangle

            for (int tv = 0; tv < TRIANGLE_VERTICES; tv++){ //read triangle vertices

                int texturePoint = this->geometry.at(m)->triangles.at(tr).v[tv].texcoord;
                float s = texcoordList.at(texturePoint).s;
                float t = 1.0f - texcoordList.at(texturePoint).t;
                glTexCoord2f(s, t);

                int vertexPoint = this->geometry.at(m)->triangles.at(tr).v[tv].position;
                float x = vertexList.at(vertexPoint).x;
                float y = vertexList.at(vertexPoint).y;
                float z = vertexList.at(vertexPoint).z;
                // glColor3f(tv == 0 ? 1 : 0, tv == 1 ? 1 : 0, tv == 2 ? 1 : 0);
                glVertex3f(x, y, z);
            }
        }
    }
    glEnd();
}