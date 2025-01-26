#include <GL/glew.h>

#include "shader.h"
#include "planetShader.h"


PlanetShader::PlanetShader(){
    loadShader(
        R"cut(
            #version 120
            #define gl_ViewMatrix gl_ModelViewMatrix
            varying vec4 currentVertex;
            varying vec3 currentNormal;
            varying vec4 lightVertex;
            uniform vec4 lightPos;
            uniform mat4 modelMatrix;
            varying vec3 vertex;

            void main(){
                currentVertex = modelMatrix * gl_Vertex;
                currentNormal = mat3(modelMatrix) * gl_Vertex.xyz;
                lightVertex = lightPos;
                vertex = gl_Vertex.xyz;

                gl_Position = gl_ProjectionMatrix * gl_ViewMatrix * currentVertex;
            }
        )cut",
        R"cut(
            varying vec4 currentVertex;
            varying vec3 currentNormal;
            varying vec4 lightVertex;
            
            uniform sampler2D tex;
            varying vec3 vertex;
            
            void main(){
                vec3 zeroVertex = vec3(0.0, 0.0, 0.0);
                vec3 lightVec = normalize(lightVertex.xyz- zeroVertex);
                vec3 normal = normalize(currentNormal);
        
                float result = max(dot(normal, lightVec), 0.05);

                vec3 v = normalize(vertex);
                float x = v.x;
                float y = v.y;
                float z = v.z;
                float phi = 1.0 - (1.0 + atan(x, -z) / 3.1415) / 2.0;
                float theta = acos(y) / 3.1415;
                vec2 st = vec2(phi, theta);

                vec3 color = vec3(result, result, result);
                gl_FragColor = vec4(texture2D(tex, st).rgb * result, 1.0);
            }
        )cut"
    );

    texID = Shader::uniformLocation("tex");
    glUniform1i(texID, 0);
    sunID = Shader::uniformLocation("lightPos");
    modelMatrixID = Shader::uniformLocation("modelMatrix");
}