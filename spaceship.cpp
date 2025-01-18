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

Matrix4 Spaceship::makeModelMatrix(){ //right now works bad :(
    if (body == 0)
        return Object::makeModelMatrix();
    
    Matrix4 bodyMatrix;
    NewtonBodyGetMatrix(body, bodyMatrix.ptr());
    return bodyMatrix;
}
// #end of pack

// check and use movement
void Spaceship::ApplyForceAndTorque(){
    if (underControl){
        Vec3 movement {0, 0, 0};
        Matrix4 bodyMatrix;
        NewtonBodyGetMatrix(body, bodyMatrix.ptr());
        

        if (currentActionStatus & ACTION_MOVE_FORWARD){
            Vec3 forward(0, 0, -1);
            movement = movement + multiplyMatrixVec(bodyMatrix, forward);
        }

        if (currentActionStatus & ACTION_MOVE_BACK){
            Vec3 forward(0, 0, 1);
            movement = movement + multiplyMatrixVec(bodyMatrix, forward);
        }

        if (currentActionStatus & ACTION_MOVE_LEFT){
            Vec3 forward(-1, 0, 0);
            movement = movement + multiplyMatrixVec(bodyMatrix, forward);
        }
        
        if (currentActionStatus & ACTION_MOVE_RIGHT){
            Vec3 forward(1, 0, 0);
            movement = movement + multiplyMatrixVec(bodyMatrix, forward);
        }

        if (currentActionStatus & ACTION_MOVE_UP){
            Vec3 forward(0, 1, 0);
            movement = movement + multiplyMatrixVec(bodyMatrix, forward);
        }

        if (currentActionStatus & ACTION_MOVE_DOWN){
            Vec3 forward(0, -1, 0);
            movement = movement + multiplyMatrixVec(bodyMatrix, forward);
        }

        // use movement vector on spaceship
        float vec[3] {movement.x, movement.y, movement.z};
        NewtonBodySetForce(body, vec);
        
        //#####
        Vec3 rotation {0, 0, 0};

        if (currentActionStatus & ACTION_ROLL_CW){
            Vec3 rotate {0.01, 0, 0};
            rotation = rotation + multiplyMatrixVec(bodyMatrix, rotate);
        }

        if (currentActionStatus & ACTION_ROLL_CCW){
            Vec3 rotate {-0.01, 0, 0};
            rotation = rotation + multiplyMatrixVec(bodyMatrix, rotate);
        }

        if (currentActionStatus & ACTION_YAW_CW){
            Vec3 rotate {0, 0.01, 0};
            rotation = rotation + multiplyMatrixVec(bodyMatrix, rotate);
        }

        if (currentActionStatus & ACTION_YAW_CCW){
            Vec3 rotate {0, -0.01, 0};
            rotation = rotation + multiplyMatrixVec(bodyMatrix, rotate);
        }

        if (currentActionStatus & ACTION_PITCH_UP){
            Vec3 rotate {0, 0, 0.01};
            rotation = rotation + multiplyMatrixVec(bodyMatrix, rotate);
        }

        if (currentActionStatus & ACTION_PITCH_DOWN){
            Vec3 rotate {0, 0, -0.01};
            rotation = rotation + multiplyMatrixVec(bodyMatrix, rotate);
        }

        float rot[3] {rotation.x, rotation.y, rotation.z};
        NewtonBodyAddTorque(body, rot);
    }
}