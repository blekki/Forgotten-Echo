#pragma once

// #include "ForgottenEcho.h"
#include "shader/sunShader.h"

#include "entity.h"
#include "sphere.h"

class Sun: public Entity
{
    private:
        int ID = 0;
        float scale = 1.0f;        
        GLuint coronaTexture;
        GLuint framebuffer;

        Matrix4 makeModelMatrix(xyz_t follow);

    public:
        void setScale(float scale);
        void draw(xyz_t follow);
        void draw(SunShader &sunShader, xyz_t follow);

        int screen_width;
        int screen_height;

        Sun();
};