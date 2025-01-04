#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <GL/gl.h>
#include <SOIL/SOIL.h>

#include "model.h"

using namespace std;

void Model::setPath(string path){
    this->path = path;
}

void Model::setMaterials(string fileName){
    ifstream input(fileName);
    string textline;

    // string path = "models/Turanic Raiders/Raiders Ion Array Frigate/lod0/";

    // materialList.push_back(0);
    string materialName;
    while (getline(input, textline, ' ')) {

        if (textline == "newmtl"){
            input >> materialName;
            input.get();
            continue;
        }
        
        if (textline == "map_Kd"){
            string textureName;
            input >> textureName;

            if (materialList[materialName].textureID == 0){ 
                int textureID = SOIL_load_OGL_texture((this->path + textureName).c_str(), SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
                cout << "setMaterial: " << textureID << " : " << textureName << endl;
                materialList[materialName].textureID = textureID;
            }
            input.get();
            continue;
        }

        // if input have something else, skip iteration
        getline(input, textline);
    }

    cout << "materrial was correctly read -> " << fileName << endl;
    input.close();
}

void Model::setModel(string fileName){
    ifstream input(fileName);
    string textline;

    Mesh* currentMesh = 0;
    // zero index was added for comfortability.
    // some later when triangles is drawing zero index gives
    // posibilities don't plus unit every time for every vertex
    vertexList.push_back(xyz_t(0, 0, 0));
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
            input >> currentMesh->material;
            input.get();
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
        
        //--> if textline == other symbol
        //--> include comments (#), right now unneeded symbols (o, s)
        getline(input, textline);
    }
    if (currentMesh != 0) {
        geometry.push_back(currentMesh);
    }

    cout << "model was correctly read -> " << fileName << endl;
    input.close();
}    
