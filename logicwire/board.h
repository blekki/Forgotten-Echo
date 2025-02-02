#pragma once
#include <string>
#include <iostream>

using namespace std;

class Board
{
    private:
        // string name;
        int width;
        int height;
        uint* board;

    public:
        class Row
        {
            private:
                uint *ptr;
            public:
                Row(uint* ptr) : ptr(ptr){};
                uint operator[](int i){
                    return ptr[i];
                }
                void addWire(int i, int wire) {
                    ptr[i] = wire + 48; // 48 means 0 in ASCII
                }
        };

    public:
        
        Board(){
            width = 0;
            height = 0;
            uint* board = nullptr; // ???
        }

        ~Board(){
            if (board) delete[] board;
        }

        int getWidth();
        int getHeight();

        void load(const char* circuit, int height);
        void emptyBoard(int height, int width);
        void print();

        uint operator()(int column, int row){
            return board[row * width + column]; // literally board[row, column]
        }

        Row operator[](int row){
            return Row(&board[row * width]);
        }
};