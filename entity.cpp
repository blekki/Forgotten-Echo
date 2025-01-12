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

void Entity::prepareRotation(float rotX, float rotY, float rotZ){
    constexpr float PI_DIV_180 = 3.1415 / 180.0f;
    Matrix4 basicRotate;
    Qued qued;
    // axis primal vectors
    Vec3 fromX(1, 0, 0);
    Vec3 fromY(0, 1, 0);
    Vec3 fromZ(0, 0, 1);
    // new position vectors
    Vec3 toX(cos(rotX * PI_DIV_180), sin(rotX * PI_DIV_180), 0);
    Vec3 toY(0, cos(rotY * PI_DIV_180), sin(rotY * PI_DIV_180));
    Vec3 toZ(sin(rotZ * PI_DIV_180), 0, cos(rotZ * PI_DIV_180));

    // make new rotate matrix
    qued.newQued(fromX, toX);
    basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));
    qued.newQued(fromY, toY);
    basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));
    qued.newQued(fromZ, toZ);
    basicRotate = multiplyMatrix(basicRotate, rotationMatrix(qued));

    // push new matrix
    rotation = multiplyMatrix(rotation, basicRotate);
}
