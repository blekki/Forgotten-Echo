#include <vector>
#include <functional>
#include <png++/png.hpp>

#include "logicwire.h"

enum direction_t{
    RIGHT_DIRECTION,
    LEFT_DIRECTION,
    TOP_DIRECTION,
    BOTTOM_DIRECTION,
};

void LogicWire::loadCircuit(const char* image_source){
    // image into board
    png::image<png::rgb_pixel> image(image_source);
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

    // giving an id for every inputs and outputs
    // addition, draw wire on board a place with pins
    uint input = 0;
    uint output = 0;
    for (int y = 0; y < board.getHeight(); y++) { // input wires
        if (board(0, y)) {
            inputs.push_back(Input(input));
            input++;
            map[y].addWire(0, 0); // "0" id for inputs and outputs
        }
        
        int last_x = board.getWidth() - 1;
        if (board(last_x, y)) {
            outputs.push_back(Output(output));
            output++;
            map[y].addWire(last_x, 0); //##################
        }
    }
    
    // serching wires and bridges
    unsigned short int wire = 0;
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
                // use functions
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
                            case RIGHT_DIRECTION:
                                walker(x+1, y); break;
                            case LEFT_DIRECTION:
                                walker(x-1, y); break;
                            case TOP_DIRECTION:
                                walker(x, y+1); break;
                            case BOTTOM_DIRECTION:
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
                        powerTheWire(wire, true);
                    
                    // check bridge
                    (board(x+1, y)) ? walker(x+1, y) : bridge(x+1, y, RIGHT_DIRECTION );
                    (board(x-1, y)) ? walker(x-1, y) : bridge(x-1, y, LEFT_DIRECTION  );
                    (board(x, y+1)) ? walker(x, y+1) : bridge(x, y+1, TOP_DIRECTION   );
                    (board(x, y-1)) ? walker(x, y-1) : bridge(x, y-1, BOTTOM_DIRECTION);
                    
                };
                walker(x, y);
            }
        }
    
    }

    // connecting inputs with wire
    int in = 0;
    int out = 0;
    for (int row = 0; row < board.getHeight(); row++) {
        if (map(0, row)) {
            inputs[in].setLocalConnection(map(1, row));
            in++;
        }

        int last_x = board.getWidth() - 1;
        if (map(last_x, row)) {
            outputs[out].setLocalConnection(map(last_x - 1, row));
            out++;
        }
    }
    
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

    // prepare containers for future states
    next_input_states.resize(inputs.size());
    next_wire_states.resize(wires.size());
    next_output_states.resize(outputs.size());
}

// ############# OTHER FUNCTIONS #############

void LogicWire::powerTheWire(int id, bool status){
    this->wires.at(id) = true;
}

void LogicWire::simulate(){
    // delete alredy applied states
    for (uint i = 0; i < next_wire_states.size(); i++)
        next_wire_states.at(i) = false;
    for (uint i = 0; i < next_output_states.size(); i++)
        next_output_states.at(i) = false;

    // (local connection) wires get power from inputs
    for (uint a = 0; a < inputs.size(); a++) {
        if (inputs[a].checkPower())
            next_wire_states[inputs[a].getLocalConnection()] = true;
    }

    // gates stop/push power
    for (uint a = 0; a < gates.size(); a++) {
        Gate& gate = gates[a];
        bool source_powered = wires[gate.source];
        if (!source_powered)
            next_wire_states[gate.drain] = true;
    }

    // (local connection) outputs get power from wires
    for (uint a = 0; a < outputs.size(); a++) {
        // output is a part of wire 
        // (if wire power changes, output changes it too)
        if (next_wire_states[outputs[a].getLocalConnection()]) 
            next_output_states.at(a) = true;
    }
    
    print();
}

void LogicWire::applyChanges(){

    for (uint a = 0; a < wires.size(); a++) {
        wires[a] = next_wire_states[a];
    }

    for (uint a = 0; a < outputs.size(); a++) {
        outputs[a].setPower(next_output_states[a]);
    }
    
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

LogicWire::LogicWire(const char* image_source){
    loadCircuit(image_source);
}