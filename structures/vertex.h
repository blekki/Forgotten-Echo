#pragma once

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