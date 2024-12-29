#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

#include "object.h"

using namespace std;

//set basic object characteristics
void Object::setPosition(float x, float y, float z){
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

void Object::setRotate(float angleX){
//     this->angleX = angleX;
    // this->angleY = angleY;
}

void Object::setScale(float scale){
    this->scale = scale;
}

//draw object on screen
void Object::drawTriangles(){
    const int TRIANGLE_VERTICES = 3;
    glColor3f(1.0f, 1.0f, 1.0f);
    
    if (this->ID == 0){
        this->ID = glGenLists(1);
        glNewList(ID, GL_COMPILE);
        
        int meshCount = this->geometry.size();

        for (int m = 0; m < meshCount; m++) { //read every mesh with triangles
            glBindTexture(GL_TEXTURE_2D, materialList[geometry.at(m)->material].textureID);
            glBegin(GL_TRIANGLES);
            // cout << "textureID: " << this->materialList[geometry.at(m)->material].textureID << endl;

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
                    glVertex3f(x, y, z);
                }
            }
            glEnd();
        }
        glEndList();
    }
    glCallList(this->ID);
}