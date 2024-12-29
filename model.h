#pragma once
// #include <iostream>
// #include <stdlib.h>
// #include <fstream>
#include <vector>
#include <string>
#include <map>

#include "structures/xyz.h"
#include "structures/st.h"
#include "structures/vertex.h"

using namespace std;

class Model{
    protected:
        int ID = 0;

        struct Triangle
        {
            Vertex v[3];
        };

        struct Material
        {
            int textureID;

            Material(int textureID){
                this->textureID = textureID;
            }
            Material(){
                this->textureID = 0;
            }
        };

        struct Mesh
        {
            string material;
            vector<Triangle> triangles;
        };

        void setModel(string fileName);
        void setMaterials(string fileName);

    public:
        virtual void newModel(string fileName){
            setModel(fileName);
        }
        virtual void newMaterials(string fileName){
            setMaterials(fileName);
        }


        Model(){};
        virtual ~Model(){};
    
    protected:
    public:
        vector<xyz_t> vertexList;
        vector<st_t> texcoordList;
        vector<xyz_t> normalList;
        map<string, Material> materialList;
        
        vector<Mesh*> geometry;
};