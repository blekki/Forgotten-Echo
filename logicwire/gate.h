#pragma once
#include <iostream>

using namespace std;

class Gate
{
    public:
        const int id;
        const int source;
        const int drain;

    public:
        void print();
        
        Gate(int id, int source, int drain)
        :   id(id), source(source), drain(drain)
        {}
};