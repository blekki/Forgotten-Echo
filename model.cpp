#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <GL/gl.h>

#include "model.h"

using namespace std;

//<><><> structures
struct xyz_t;
struct st_t;
struct Vertex;
struct Triangle;
struct Mesh;

void Model::setModel(string fileName){
    // fileName = "models/Carrier-T.obj";
    ifstream input(fileName);
    string textline;

    //todo: skip comments
    //todo: read material filename
    //todo: skip object

    getline(input, textline);
    getline(input, textline);
    getline(input, textline);
    getline(input, textline);

    Mesh* currentMesh = 0;
    vertexList.push_back(xyz_t(0, 0, 0)); //#########################
    texcoordList.push_back(st_t(0, 0));
    normalList.push_back(xyz_t(0, 0, 0));

    while (getline(input, textline, ' ')) {
        
        if (textline == "v") {
            float x;
            input >> x;
            float y;
            input >> y;
            float z;
            input >> z;
            vertexList.push_back(xyz_t(x, y, z));

            input.get();
            continue;
        }

        if (textline == "vt") {
            float s;
            input >> s;
            float t;
            input >> t;
            texcoordList.push_back(st_t(s, t));

            input.get();
            continue;
        }

        if (textline == "vn") {
            float x;
            input >> x;
            float y;
            input >> y;
            float z;
            input >> z;
            normalList.push_back(xyz_t(x, y, z));

            input.get();
            continue;
        }
        
        if (textline == "usemtl") {
            if(currentMesh != 0){
                geometry.push_back(currentMesh);
            }
            currentMesh = new Mesh();

            string name;
            getline(input, name);
            continue;
        }

        if (textline == "f") {
            Triangle face;
            int a;
            int b;
            int c;
            char ch;

            for (int i = 0; i < 3; i++) {
                input >> a >> ch >> b >> ch >> c;
                input.get();
                face.v[i] = Vertex(a, b, c);
            }
            currentMesh->triangles.push_back(face);
            continue;
        }

        if (textline == "s"){
            int j;
            input >> j;
            input.get();
            continue;
        }
    }
    if (currentMesh != 0) {
        geometry.push_back(currentMesh);
    }

    input.close();
}    
