#pragma once

#include "shader.h"

class SunShader: public Shader
{
    private:
        int sunID;
        int texID;
        int positionID;
        int timeID;
        int modelMatrixID;

    public:
        void setSun(xyz_t position){
            Shader::setVec4(sunID, position);
        }

        void setPosition(xyz_t position){
            Shader::setVec4(positionID, position);
        }

        void setTime(float time){
            Shader::setFloat(timeID, time);
        }

        void setModelMatrix(Matrix4 modelMatrix){
            Shader::setMatrix4(modelMatrixID, modelMatrix);
        }

        SunShader();
};