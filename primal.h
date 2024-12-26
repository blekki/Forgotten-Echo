#pragma once

class Primal{
    private:
        void createTriangle();
        void createCircle(float radius);
        void createSphere(int section);

    public:
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