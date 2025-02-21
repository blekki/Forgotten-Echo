#pragma once
#include <vector>
#include <functional>

#include "board.h"
#include "gate.h"


using namespace std;

class LogicWire
{
    private:
        Board board;
        vector<bool> wires;
        vector<Gate> gates;

        Board map; // in the future: replace it to the LogicWire function
        
        void load(const char* circuit, int height);
    
    public:
        LogicWire(const char* image_source);

        void simulate();
        void powerTheWire(int id);
        void print(); // in future i won't need it
};