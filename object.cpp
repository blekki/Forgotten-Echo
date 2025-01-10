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

void Object::setScale(float scale){
    this->scale = scale;
}

// a pack of returning position XYZ
//#####
float Object::getX(){
    return position.x;
}

float Object::getY(){
    return position.y;
}

float Object::getZ(){
    return position.z;
}

xyz_t Object::getXYZ(){
    return position;
}
//##########
Matrix4 Object::getRotate(){
    return rotate;
}

Matrix4 Object::makeModelMatrix(){
    Matrix4 matrix;
    glPushMatrix();
    glLoadIdentity();
    // glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
    glTranslated(position.x, position.y, position.z);
    // glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
    glScalef(scale, scale, scale);
    // glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
    // glMultMatrixf(rotationPosition.ptr());
    // glGetFloatv(GL_MODELVIEW_MATRIX, matrix.ptr());
    glPopMatrix();
    return matrix;
}

void Object::prepareRotate(float rotX, float rotY, float rotZ){
    constexpr float PI_DIV_180 = 3.1415 / 180.0f;
    Matrix4 basicRotate;
    Qued qued;
    // axis primal vectors
    Vec3 fromX(1, 0, 0);
    Vec3 fromY(0, 1, 0);
    Vec3 fromZ(0, 0, 1);
    // new position vectors
    Vec3 toX(cos(rotX * PI_DIV_180), sin(rotX * PI_DIV_180), 0);
    Vec3 toY(0, cos(rotY * PI_DIV_180), sin(rotY * PI_DIV_180));
    Vec3 toZ(sin(rotZ * PI_DIV_180), 0, cos(rotZ * PI_DIV_180));

    // make new rotate matrix
    qued.newQued(fromX, toX);
    basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));
    qued.newQued(fromY, toY);
    basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));
    qued.newQued(fromZ, toZ);
    basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));

    // push new matrix
    rotate = multiplyMatrix(rotate, basicRotate);
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