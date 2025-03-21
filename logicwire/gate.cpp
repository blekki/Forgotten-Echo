#include "gate.h"

void Gate::print(){
    cout << "gate " << id << ": " << source << " -> " << drain << endl;
}