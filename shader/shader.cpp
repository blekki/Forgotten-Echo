#include <iostream>
#include <vector>

#include <GL/glew.h>
#include "../matrices.h"
#include "../structures/xyz.h"

#include "shader.h"

using namespace std;

GLuint Shader::getShaderID(){
    return programID;
}

void Shader::setFloat(int index, float value){
    glUniform1f(index, value);
}

void Shader::setInteger(int index, int value){
    glUniform1i(index, value);
}

void Shader::setMatrix4(int index, Matrix4 &matrix4){
    glUniformMatrix4fv(index, 1, false, matrix4.ptr());
}

void Shader::setVec4(int index, xyz_t vec4){
    glUniform4f(index, vec4.x, vec4.y, vec4.z, 1);
}

void Shader::loadShader(string vertexSource, string fragmentSource){
    // ### vectex shader ###
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(vertexShader);
        clog << "infolog: " << (char*) infoLog.data() << endl;        
        throw "[error] vertex shader wasn't compiled";
    }

    // ### fragment shader ###
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        clog << "infolog: " << (char*) infoLog.data() << endl;
        throw "[error] fragment shader wasn't compiled";
    }

    // ### repeiring shader ###
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        clog << "infolog: " << (char*) infoLog.data() << endl;
        throw "[error] shader wasn't linked";
    }

    // complite shader
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    // clog << "[SHADER]: shader loaded" << endl;
    programID = program;
}