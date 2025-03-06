#include "output.h"

using namespace std;

void Output::setLocalConnection(uint wire_id){
    this->connection = wire_id;
}
uint Output::getLocalConnection(){
    return connection;
}