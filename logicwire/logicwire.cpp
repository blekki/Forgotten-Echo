#include "logicwire.h"
#include <vector>
#include <functional>
#include <png++/png.hpp>


void LogicWire::load(const char* circuit, int height){
    board.load(circuit, height);
    map.emptyBoard(board.getHeight(), board.getWidth());
    
    int wire = 0;
    for (int y = 1; y < board.getHeight() - 1; y++) {
        for (int x = 1; x < board.getWidth() - 1; x++) {
            if (board(x, y) && !map(x, y)) {
                wire++;
                function<void(int, int)> walker;
                walker = [&](int x, int y) {
                    if (map(x,y))
                        return;
                    map[y].addWire(x, wire);
                    if (board(x+1, y))
                        walker(x+1, y);
                    if (board(x-1, y))
                        walker(x-1, y);
                    if (board(x, y+1))
                        walker(x, y+1);
                    if (board(x, y-1))
                        walker(x, y-1);
                };
                walker(x, y);
            }
        }
    
    }
    board.print(); //for debug
    cout << "----------------" << endl;
    map.print(); //for debug

    // searching gates
    wires.resize(wire+1); // "0" index for non existent wire
    // cout << "wires count: " << wire << endl; // for debug
    
    int gate = 0;
    for (int y = 2; y < board.getHeight() - 2; y++) {
        for (int x = 2; x < board.getWidth() - 2; x++) {
            long mask = 0x000000000;
            if(board(x-1, y-1)) mask |= 0x100000000;
            if(board(x  , y-1)) mask |= 0x010000000;
            if(board(x+1, y-1)) mask |= 0x001000000;
            if(board(x-1, y  )) mask |= 0x000100000;
            if(board(x  , y  )) mask |= 0x000010000;
            if(board(x+1, y  )) mask |= 0x000001000;
            if(board(x-1, y+1)) mask |= 0x000000100;
            if(board(x  , y+1)) mask |= 0x000000010;
            if(board(x+1, y+1)) mask |= 0x000000001;

            // gate types
            switch (mask) {
                // left-to-right
                case 0x110101110:
                    gate++;
                    gates.push_back(Gate(gate, map(x-1,y), map(x+1,y))); // -48 for convert char number into int
                    break;
                // right-to-left
                case 0x011101011:
                    gate++;
                    gates.push_back(Gate(gate, map(x+1,y), map(x-1,y)));
                    break;
                // top-to-bottom
                case 0x111101010:
                    gate++;
                    gates.push_back(Gate(gate, map(x,y-1), map(x,y+1)));
                    break;
                // bottom-to-top
                case 0x010101111:
                    gate++;
                    gates.push_back(Gate(gate, map(x,y+1), map(x,y-1)));
                    break;
                default: break;
            }
        }
    }
    // cout << "gates count: " << gate << endl; // for debug
}

LogicWire::LogicWire(const char* image_name){
    png::image<png::rgb_pixel> image(image_name);
    string circuit = "";

    for (int a = 0; a < image.get_height(); a++) {
        for (int b = 0; b < image.get_width(); b++) {
            int color_mesh = image[a][b].red +
                             image[a][b].green +
                             image[a][b].blue;

            char symbol;
            switch (color_mesh) {
                case 255*3: symbol = '#'; break;
                case 100*3: symbol = '@'; break;
                default: symbol = ' '; break;
            }
            circuit.push_back(symbol);
        }
    }

    for (int a = 0; a < image.get_height(); a++) {
        for (int b = 0; b < image.get_width(); b++) {
            cout << circuit[a * image.get_width() + b];
        }
        cout << endl;
    }
    
    load(circuit.c_str(), image.get_height());
    
}

void LogicWire::simulate(){
    vector<bool> new_states;
    new_states.resize(wires.size());

    for (int i = 0; i < gates.size(); i++) {
        Gate& gate = gates[i];
        bool source_powered = wires[gate.source];
        if (!source_powered)
            new_states.at(gate.drain) = true;
    }

    wires = new_states;
}

void LogicWire::powerTheWire(int id){
    this->wires.at(id) = true;
}

// in future i won't need it
void LogicWire::print(){
    const char* bright = "\033[32m";
    const char* normal = "\033[37m";
    const char* reset = "\033[0m";

    for (int y = 0; y < board.getHeight(); y++) {
        for (int x = 0; x < board.getWidth(); x++) {
            int wire = map(x, y);
            char v = (board(x, y));
            cout << (wires[wire] ? bright : normal)
                    << (v ? v : ' ');
        }
        cout << reset << endl;
    }
}