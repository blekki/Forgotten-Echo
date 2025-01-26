#include "iostream"
#include <GL/glew.h>
#include "ForgottenEcho.h"

#include "cursor.h"

void Cursor::setX(double x){
    this->xPos = x;
}
void Cursor::setY(double y){
    this->yPos = y * -1;
}

void Cursor::pushWindowSize(int x, int y){
    this->screen_width  = x;
    this->screen_height = y;
}

double Cursor::getX(){
    return xPos;
}
double Cursor::getY(){
    return yPos;
}

double Cursor::getTransformX(){
    return (xPos - (screen_width / 2.0f));
}
double Cursor::getTransformY(){
    return (yPos + (screen_height / 2.0f));
}

void Cursor::printXY(){
    cout << Cursor::getTransformX() << " : " << Cursor::getTransformY() << endl;
}

void Cursor::draw(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(xPos / screen_width, yPos / screen_height, 0); //todo: remake
    glBegin(GL_LINES);
    glVertex2f(-0.2, 0);
    glVertex2f(0.2, 0);
    glVertex2f(0, -0.2);
    glVertex2f(0, 0.2);
    glEnd();
    glPopMatrix();
}
