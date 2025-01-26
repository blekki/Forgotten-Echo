#include "iostream"
#include <GL/glew.h>
#include "ForgottenEcho.h"

#include "cursor.h"

void Cursor::setX(double x){
    this->x = x;
}
void Cursor::setY(double y){
    this->y = y * -1;
}

void Cursor::pushWindowSize(int x, int y){
    this->screen_width  = x;
    this->screen_height = y;
}

double Cursor::getX(){
    return x;
}
double Cursor::getY(){
    return y;
}

double Cursor::getTransformX(){
    return (x - (screen_width / 2.0f));
}
double Cursor::getTransformY(){
    return (y + (screen_height / 2.0f));
}

void Cursor::printXY(){
    cout << getTransformX() << " : " << getTransformY() << endl;
}

void Cursor::draw(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(getTransformX() / screen_width, getTransformY() / screen_height, 0); //todo: remake
    glBegin(GL_LINES);
    glVertex2f(-0.2, 0);
    glVertex2f(0.2, 0);
    glVertex2f(0, -0.2);
    glVertex2f(0, 0.2);
    glEnd();
    glPopMatrix();
}
