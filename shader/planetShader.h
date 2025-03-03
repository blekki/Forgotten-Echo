#pragma once

#include "shader.h"

class PlanetShader: public Shader
{
    private:
        int sunID;
        int texID;
        int modelMatrixID;

    public:
        void setSun(xyz_t position){
            Shader::setVec4(sunID, position);
        }

        void setModelMatrix(Matrix4 matrix4){
            Shader::setMatrix4(modelMatrixID, matrix4);
        }

        PlanetShader();
};