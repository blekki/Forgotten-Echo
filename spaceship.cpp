#include "Newton.h"

#include "spaceship.h"

void Spaceship::setControlStatus(bool newStatus){
    this->underControl = newStatus;
}

void Spaceship::pushActionStatus(int newStatus){
    this->currentActionStatus = newStatus;
}

void Spaceship::setNewtonBody(NewtonBody *body){
    this->body = body;
    NewtonBodySetUserData(body, this);
}

// pack of return position functions
float Spaceship::getX(){
    if (body == 0) 
        return Object::getX();
    Matrix4 bodyMatrix;
    NewtonBodyGetMatrix(body, bodyMatrix.ptr());
    return bodyMatrix.ptr()[12];
}

float Spaceship::getY(){
    if (body == 0)
        return Object::getY();
    Matrix4 bodyMatrix;
    NewtonBodyGetMatrix(body, bodyMatrix.ptr());
    return bodyMatrix.ptr()[13];
}

float Spaceship::getZ(){
    if (body == 0)
        return Object::getZ();
    Matrix4 bodyMatrix;
    NewtonBodyGetMatrix(body, bodyMatrix.ptr());
    return bodyMatrix.ptr()[14];
}

xyz_t Spaceship::getXYZ(){
    if (body == 0)
        return Object::getXYZ();

    Matrix4 bodyMatrix;
    xyz_t position;
    NewtonBodyGetMatrix(body, bodyMatrix.ptr());
    position.x = bodyMatrix.ptr()[12];
    position.y = bodyMatrix.ptr()[13];
    position.z = bodyMatrix.ptr()[14];
    return position;
}
// #end of pack

// check and use movement
void Spaceship::ApplyForceAndTorque(){
    if (underControl){
        Vec3 movement;

        if (currentActionStatus & ACTION_MOVE_FORWARD){
            Vec3 forward(0, 0, -1);
            movement = movement + multiplyMatrixVec(rotation, forward);
        }

        if (currentActionStatus & ACTION_MOVE_BACK){
            Vec3 forward(0, 0, 1);
            movement = movement + multiplyMatrixVec(rotation, forward);
        }

        if (currentActionStatus & ACTION_MOVE_LEFT){
            Vec3 forward(-1, 0, 0);
            movement = movement + multiplyMatrixVec(rotation, forward);
        }
        
        if (currentActionStatus & ACTION_MOVE_RIGHT){
            Vec3 forward(1, 0, 0);
            movement = movement + multiplyMatrixVec(rotation, forward);
        }

        if (currentActionStatus & ACTION_MOVE_UP){
            Vec3 forward(0, 1, 0);
            movement = movement + multiplyMatrixVec(rotation, forward);
        }

        if (currentActionStatus & ACTION_MOVE_DOWN){
            Vec3 forward(0, -1, 0);
            movement = movement + multiplyMatrixVec(rotation, forward);
        }

        // use movement vector on spaceship
        float vec[3] {movement.x, movement.y, movement.z};
        NewtonBodySetForce(body, vec);
    }
}