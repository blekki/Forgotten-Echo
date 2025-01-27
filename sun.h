#pragma once

// #include "ForgottenEcho.h"
#include "shader/sunShader.h"

#include "entity.h"
#include "sphere.h"

class Sun: public Entity
{
    private:
        float scale = 1.0f;
        GLuint coronaTexture;
        GLuint framebuffer;

        int screen_width;
        int screen_height;

        Matrix4 makeModelMatrix(xyz_t follow);

    public:
        void setScale(float scale);
        void pushWindowSize(GLFWwindow *window);

        void prerender(SunShader &sunShader);
        void draw(xyz_t follow);

        Sun();
};