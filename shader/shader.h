#pragma once
#include <fstream>
#include <GL/glew.h>


#include "../structures/xyz.h"
#include "../matrices.h"

using namespace std;

class Shader
{
    protected:
        GLuint programID;

        void loadShader(string vertexSource, string fragmentSource);
        void setFloat(int index, float value); // glUniform1d()
        void setInteger(int index, int value);
        void setMatrix4(int index, Matrix4 &matrix4);
        void setVec4(int index, xyz_t vec4);

        int uniformLocation(string name);

    public:
        GLuint getShaderID();
        // void loadShader(string vertexSource, string fragmentSource);
        // GLuint loadShaider(string vertexSource, string fragmentSource){
        //     return load(vertexSource, fragmentSource);
        // }
};