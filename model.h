#pragma once
#include <vector>
#include <string>
#include <map>

#include "structures/xyz.h"
#include "structures/st.h"
#include "structures/vertex.h"

using namespace std;

class Model
{
    protected:
        int ID = 0;
        string path;

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

    public:
        virtual void loadModel(string fileName);
        virtual void loadMaterials(string fileName);
        void setPath(string path);

        Model(){};
        virtual ~Model(){};
    
    protected:
        vector<xyz_t> vertexList;
        vector<st_t> texcoordList;
        vector<xyz_t> normalList;
        map<string, Material> materialList;
        
        vector<Mesh*> geometry;
};