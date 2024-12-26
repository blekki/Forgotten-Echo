#include <math.h>
#include <GL/gl.h>

#include "primal.h"

//draw simple 2d triangle
void Primal::createTriangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}

// draw a 2d circle
void Primal::createCircle(float radius)
{
    const float PiDiv180 = 3.1415f / 180.0f;
    float x = 0;
    float y = 0;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        x = radius * cos(i * PiDiv180);
        y = radius * sin(i * PiDiv180);
        glColor3f(x, y, 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}

//==============================================================
//next a couple function is needed for creation simple 3d sphere
//==============================================================

void sphereCap(int section, int position)
{
    //position means where hat must be created.
    //   "1" - upper
    //   "-1" - lower

    float stk = (1.57f - 3.14f / (float)section) * position; //1.57 = pi/2

    glColor3f(1.0f, 1.0f * position, 0.0f); //unneedy color changer (was added only for testing)

    //create sphere caps
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 1.0f * position, 0.0f); //pole point
    //other section line points
    for (int sector = 0; sector <= section; sector++) {
        float sec = (6.28f * (float)sector / (float)section) * position; //6.28 = pi * 2
        glVertex3f(cos(stk) * cos(sec), sin(stk), cos(stk) * sin(sec));
    }
    glEnd();
}

void Primal::createSphere(int section) 
{
    //upper pole
    sphereCap(section, 1);

    for (int stack = 1; stack < section - 1; stack++) { // sections up to down
        glBegin(GL_QUAD_STRIP);
        for (int sector = 0; sector <= section; sector++) { // sections around
            float stk = 1.57f - 3.14f * (float)stack / (float)section;  //1.57 = pi/2
            float sec = 6.28f * (float)sector / (float)section;         //6.28 = pi * 2
            
            glColor3f(0.1f * sector, 0.1f * sector, 0.1f * sector);
            glVertex3f(cos(stk) * cos(sec), sin(stk), cos(stk) * sin(sec));
            //next stack line point
            stk = 1.57f - 3.14f * (float)(stack + 1) / (float)section;
            glVertex3f(cos(stk) * cos(sec), sin(stk), cos(stk) * sin(sec));
        }
        glEnd();
    }

    //lower pole
    sphereCap(section, -1);
}