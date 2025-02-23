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
        unsigned short int* board;
        // uint* board;

    public:
        class Row
        {
            private:
                unsigned short int *ptr;
            public:
                Row(unsigned short int* ptr) : ptr(ptr){};
                unsigned short int operator[](int i){
                    return ptr[i];
                }
                void addWire(int i, int wire) {
                    ptr[i] = wire;
                }
        };

    public:
        
        Board(){
            width = 0;
            height = 0;
            unsigned short int* board = nullptr; // ???
        }

        ~Board(){
            if (board) delete[] board;
        }

        int getWidth();
        int getHeight();

        void load(const char* circuit, int height);
        void emptyBoard(int height, int width);
        void print();

        unsigned short int operator()(int column, int row){
            return board[row * width + column]; // literally board[row, column]
        }

        Row operator[](int row){
            return Row(&board[row * width]);
        }
};