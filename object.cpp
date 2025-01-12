#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "object.h"

using namespace std;

void Object::setScale(float scale){
    this->scale = scale;
}

Matrix4 Object::makeModelMatrix(){
    Matrix4 matrix;
    glPushMatrix();
    glLoadIdentity();
    glTranslated(position.x, position.y, position.z);
    glScalef(scale, scale, scale);
    glMultMatrixf(rotation.ptr());
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
    glPopMatrix();
    return matrix;
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

            int triangleCount = this->geometry.at(m)->triangles.size();

            for (int tr = 0; tr < triangleCount; tr++) { //read every triangle

                for (int tv = 0; tv < TRIANGLE_VERTICES; tv++){ //read triangle vertices

                    int texturePoint = this->geometry.at(m)->triangles.at(tr).v[tv].texcoord;
                    float s = texcoordList.at(texturePoint).s;
                    float t = 1.0f - texcoordList.at(texturePoint).t;
                    glTexCoord2f(s, t);

                    {int normalPoint = this->geometry.at(m)->triangles.at(tr).v[tv].normal;
                    float x = normalList.at(normalPoint).x;
                    float y = normalList.at(normalPoint).y;
                    float z = normalList.at(normalPoint).z;
                    glNormal3f(x, y, z);}

                    {int vertexPoint = this->geometry.at(m)->triangles.at(tr).v[tv].position;
                    float x = vertexList.at(vertexPoint).x;
                    float y = vertexList.at(vertexPoint).y;
                    float z = vertexList.at(vertexPoint).z;
                    glVertex3f(x, y, z);}
                }
            }
            glEnd();
        }
        glEndList();
    }
    glCallList(this->ID);
}