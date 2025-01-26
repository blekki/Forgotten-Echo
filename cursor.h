#pragma once

using namespace std;

class Cursor
{
    private:
        double xPos;
        double yPos;

        // screen size
        int screen_width;
        int screen_height;

    public:
        void setX(double x);
        void setY(double y);
        void pushWindowSize(int x, int y);
        double getX();
        double getY();
        double getTransformX();
        double getTransformY();

        void printXY(); // todo: remove

        void draw();

        Cursor(){
            xPos = 0;
            yPos = 0;
        }
};