#pragma once

using namespace std;

class Cursor
{
    private:
        double x;
        double y;

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
            x = 0;
            y = 0;
        }
};