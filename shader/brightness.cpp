#include <GL/glew.h>

#include "shader.h"
#include "brightness.h"

Brightness::Brightness(){
    loadShader(
        R"cut(
            #version 120
            #define gl_ViewMatrix gl_ModelViewMatrix
            varying vec4 currentVertex;
            varying vec3 currentNormal;
            varying vec4 lightVertex;
            uniform vec4 lightPos;
            uniform mat4 modelMatrix;
            varying vec2 st;

            void main(){
                currentVertex = modelMatrix * gl_Vertex;
                currentNormal = mat3(modelMatrix) * gl_Normal;
                lightVertex = lightPos;

                gl_Position = gl_ProjectionMatrix * gl_ViewMatrix * currentVertex;
                st = gl_MultiTexCoord0.st;
            }
        )cut",
        R"cut(
            varying vec4 currentVertex;
            varying vec3 currentNormal;
            varying vec4 lightVertex;
            
            uniform sampler2D tex;
            varying vec2 st;
            
            void main(){
                vec3 lightVec = normalize(lightVertex.xyz- currentVertex.xyz);
                vec3 normal = normalize(currentNormal);
        
                float result = max(dot(normal, lightVec), 0.1);

                vec3 color = vec3(result, result, result);
                gl_FragColor = texture2D(tex, st) * result;
            }
        )cut"
    );

    texID = Shader::uniformLocation("tex");
    glUniform1i(texID, 0);
    sunID = Shader::uniformLocation("lightPos");
    modelMatrixID = Shader::uniformLocation("modelMatrix");
}