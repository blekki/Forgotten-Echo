#include "logicwire.h"
#include <vector>
#include <functional>
#include <png++/png.hpp>


// void LogicWire::load(const char* circuit, int height){
LogicWire::LogicWire(const char* image_name){
    // image into board
    png::image<png::rgb_pixel> image(image_name);
    string circuit = "";
    for (int a = 0; a < image.get_height(); a++) {
        for (int b = 0; b < image.get_width(); b++) {
            int color_hash = image[a][b].red +
                             image[a][b].green +
                             image[a][b].blue;
            char symbol = (color_hash > 0) ? '#' : ' '; // wire = #, other = 0
            circuit.push_back(symbol);
        }
    }
    board.load(circuit.c_str(), image.get_height());
    map.emptyBoard(image.get_height(), image.get_width());
    
    // serching wires and bridges
    int wire = 0;
    wires.push_back(false); // "0" wire. Always turn off. it doesn't exist on circuit
    for (int y = 1; y < board.getHeight() - 1; y++) {
        for (int x = 1; x < board.getWidth() - 1; x++) {
            if (board(x, y) && !map(x, y)) {
                wire++;
                wires.push_back(false);
                // prepare functions
                function<void(int, int)> walker; // <-- serching all wires
                                    // walker(x, y)
                function<void(int, int, int)> bridge; // checking for bridges
                                    // bridge(x, y, source_direction)
                                    // left = 0
                                    // right = 1
                                    // top = 2
                                    // bottom = 3
                
                bridge = [&](int x, int y, int source) {
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

                    // bridge types
                    if (mask == 0x010101010) {
                        switch (source) {
                            // from left
                            case 0:
                                walker(x+1, y); break;
                            // from right
                            case 1:
                                walker(x-1, y); break;
                            // from top
                            case 2:
                                walker(x, y+1); break;
                            // from bottom
                            case 3:
                                walker(x, y-1); break;
                            default: break;
                        }   
                    }
                };
                walker = [&](int x, int y) {
                    if (map(x,y))
                        return;
                    map[y].addWire(x, wire); //for debug map.print() try addWire(wire + 48)
                    uint color_hash = image[y][x].red +
                                      image[y][x].green +
                                      image[y][x].blue;
                    if (color_hash == 255 * 3)
                        powerTheWire(wire);
                    
                    // check bridge
                    (board(x+1, y)) ? walker(x+1, y) : bridge(x+1, y, 0); //right  direction
                    (board(x-1, y)) ? walker(x-1, y) : bridge(x-1, y, 1); //left   direction
                    (board(x, y+1)) ? walker(x, y+1) : bridge(x, y+1, 2); //top    direction
                    (board(x, y-1)) ? walker(x, y-1) : bridge(x, y-1, 3); //bottom direction
                    
                };
                walker(x, y);
            }
        }
    
    }
    
    // board.print(); //for debug
    // cout << "##############################" << endl;
    // map.print(); //for debug (don't work now)

    // searching gates
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
                    gates.push_back(Gate(gate, map(x-1,y), map(x+1,y)));
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