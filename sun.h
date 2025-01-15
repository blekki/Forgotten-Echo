#pragma once

#include "shader/sunShader.h"

#include "entity.h"
#include "sphere.h"

class Sun: public Entity
{
    private:
        int ID = 0;
        //other characteristics
        float scale = 1.0f;
        
        // void draw();
        Matrix4 makeModelMatrix();

    public:
        void setScale(float scale);
        void draw(SunShader &sunShader){
            sunShader.setModelMatrix(makeModelMatrix());
            draw();
        }
        void draw();

        Sun(){
            
        };
};