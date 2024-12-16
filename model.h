#pragma once
// #include <iostream>
// #include <stdlib.h>
// #include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Model{
    protected:
        int ID = 0;

        struct xyz_t
        {
            float x;
            float y;
            float z;
            xyz_t(float x, float y, float z){
                this->x = x;
                this->y = y;
                this->z = z;
            }
        };
        struct st_t
        {
            float s;
            float t;
            st_t(float s, float t){
                this->s = s;
                this->t = t;
            }
        };

        struct Vertex
        {
            int position;
            int texcoord;
            int normal;
            Vertex(int a, int b, int c){
                this->position = a;
                this->texcoord = b;
                this->normal = c;
            }
            Vertex(){}
        };

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
            // int material;
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