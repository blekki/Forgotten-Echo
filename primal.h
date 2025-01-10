#pragma once

class Primal{
    private:
        void createTriangle();
        void createCircle(float radius);
        void createSphere(int section);
        void createFollowCoord(float x, float y, float z, float *rotation);
        void createCoord();

    public:
        void drawFollowCoord(float x, float y, float z, float *rotation){
            createFollowCoord(x, y, z, rotation);
        }
        void drawCoord(){
            createCoord();
        }
        

        void drawTriangle(){
            createTriangle();
        }

        void drawCircle(float radius){
            createCircle(radius);
        }

        void drawSphere(int section){
            createSphere(section);
        }
};