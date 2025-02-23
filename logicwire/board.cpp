#include "board.h"

int Board::getWidth(){ 
    return this->width; 
}
int Board::getHeight(){
    return this->height;
}

void Board::load(const char* circuit, int height){
    this->height = height;

    int length = 0;
    while (circuit[length] != '\0')
        length++;
    this->width = (int) (length / height);

    this->board = new unsigned short int[width * height];

    if (circuit) {
        for (int i = 0; i < width * height; i++) {
            board[i] = (circuit[i] != ' ') ? circuit[i] : 0;
        }
    }
}

void Board::emptyBoard(int height, int width){
    this->width = width;
    this->height = height;
    this->board = new unsigned short int[width * height];

    for (int i = 0; i < width * height; i++) {
        board[i] = 0;
    }
}

void Board::print(){
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            cout << (char) ( ((*this)(column, row)) ? ((*this)(column, row)) : (' ') );
        }
        cout << endl;
    }
}