#pragma once
// #include <iostream>
// #include <stdlib.h>
// #include <fstream>
#include <vector>
#include <string>

using namespace std;

class Model{
    protected:
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

        struct Mesh
        {
            int material;
            vector<Triangle> triangles;
        };

        void setModel(string fileName);

    public:
        virtual void newModel(string fileName){
            setModel(fileName);
        }
        Model(){};
        virtual ~Model(){};
    
    protected:
        vector<xyz_t> vertexList;
        vector<st_t> texcoordList;
        vector<xyz_t> normalList;
        vector<Mesh*> geometry;
};