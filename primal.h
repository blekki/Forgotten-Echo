#pragma once
#include "matrices.h"

class Primal{
    public:
        void drawFollowCoord(Matrix4 matrix);
        void drawCoord();
        
        void drawTriangle();
        void drawCircle(float radius);
        void drawSphere(int section);
};