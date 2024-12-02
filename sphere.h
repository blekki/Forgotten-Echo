#pragma once

using namespace std;

class Sphere{
    private:
        int sphereID;
        void multiTriangle(float a[], float b[], float c[], int resolution);
    public:
        virtual void draw(){
            triangleSphere(3);
        }
    protected:
        void triangleSphere(int resolution);
        virtual void vertex(float a[]);
};
