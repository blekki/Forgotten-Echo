#include "matrices.h"

#include "entity.h"

RotationMatrixPack Entity::coupleMatrices;

//set basic object characteristics
void Entity::setPosition(float x, float y, float z){
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

// a pack of returning position XYZ
//#####
float Entity::getX(){
    return position.x;
}

float Entity::getY(){
    return position.y;
}

float Entity::getZ(){
    return position.z;
}

xyz_t Entity::getXYZ(){
    return position;
}
//##########
Matrix4 Entity::getRotation(){
    return rotation;
}

void Entity::setRotatationPosition(float x, float y, float z){
    Qued qued;
    Vec3 from(0, 0, -1);
    Vec3 to(x, y, z);

    qued.newQued(from, to);

    rotation = multiplyMatrix(rotation, rotationMatrix(qued));
}
