#pragma once

using namespace std;

class Sphere{
    private:
        const int SPHERE_RESOLUTION = 0;
        int sphereID;
        void multiTriangle(float a[], float b[], float c[], int resolution);
    public:
        virtual void draw(){
            triangleSphere(SPHERE_RESOLUTION);
        }
    protected:
        void triangleSphere(int resolution);
        virtual void vertex(float a[]);
};
