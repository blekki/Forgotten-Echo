#include "cursor.h"

#include "zerostate.h"

void Zerostate::pushWindowLink(GLFWwindow *window){
    windowLink = window;
}

Cursor* Zerostate::getCursorPtr(){
    return &cursor;
}