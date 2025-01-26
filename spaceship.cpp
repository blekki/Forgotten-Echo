#include "Newton.h"

#include "spaceship.h"
#include "structures/vec3.h"

using namespace std;

void Spaceship::setControlStatus(bool newStatus){
    this->underControl = newStatus;
}

void Spaceship::newActionStatus(int newStatus){
    this->actionStatus = newStatus;
}

void Spaceship::addActionStatus(int newStatus){
    this->actionStatus |= newStatus;
}

void Spaceship::delActionStatus(int newStatus){
    this->actionStatus &= ~newStatus;
}

void Spaceship::setNewtonBody(NewtonBody *body){
    this->body = body;
    NewtonBodySetUserData(body, this);
}

void Spaceship::setSpeedUp(float forward, float right, float up){
    this->forwardSpeedUp = Vec3(0, 0, -forward);
    this->rightSpeedUp = Vec3(-right, 0, 0);
    this->upSpeedUp = Vec3(0, up, 0);
}

void Spaceship::setRotationSpeedUp(float roll, float yaw, float pitch){
    this->rollSpeedUp = Vec3(0, 0, roll);
    this->yawSpeedUp = Vec3(0, yaw, 0);
    this->pitchSpeedUp = Vec3(pitch, 0, 0);
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

Matrix4 Spaceship::makeModelMatrix(){
    if (body == 0)
        return Object::makeModelMatrix();
    
    Matrix4 bodyMatrix;
    NewtonBodyGetMatrix(body, bodyMatrix.ptr());
    return bodyMatrix;
}
// #end of pack

void Spaceship::setRotateHanding(float value3[3]){
    NewtonBodySetAngularDamping(body, value3);
}

void Spaceship::setHanding(float value){
    NewtonBodySetLinearDamping(body, value);
}

void Spaceship::pushWindowSize(int *width, int *height){
    this->link_screen_width = width;
    this->link_screen_height = height;
}

void Spaceship::mouseRotation(double mouseX, double mouseY){
    if (abs(mouseX) < 40.0)
        mouseX = 0.0;
    if (abs(mouseY) < 40.0)
        mouseY = 0.0;
    Vec3 vec;
    vec.y = 0;
    vec.x = mouseY / 50000.0f;
    vec.z = -mouseX / 100000.0f;
    
    // cout << vec.x << " : " << vec.y << " : " << vec.z << endl;

    needToRotate = multiplyMatrixVec(makeModelMatrix(), vec);
}

// check and use movement
void Spaceship::ApplyForceAndTorque(){
    // ###### movement ######
    Vec3 movement {0, 0, 0};
    if (actionStatus & ACTION_MOVE_FORWARD)
        movement += multiplyMatrixVec(makeModelMatrix(), forwardSpeedUp);
    if (actionStatus & ACTION_MOVE_BACK)
        movement -= multiplyMatrixVec(makeModelMatrix(), forwardSpeedUp);

    if (actionStatus & ACTION_MOVE_LEFT)
        movement += multiplyMatrixVec(makeModelMatrix(), rightSpeedUp);
    if (actionStatus & ACTION_MOVE_RIGHT)
        movement -= multiplyMatrixVec(makeModelMatrix(), rightSpeedUp);

    if (actionStatus & ACTION_MOVE_UP)
        movement += multiplyMatrixVec(makeModelMatrix(), upSpeedUp);
    if (actionStatus & ACTION_MOVE_DOWN)
        movement -= multiplyMatrixVec(makeModelMatrix(), upSpeedUp);

    // use movement vector on spaceship
    float vec[3] {movement.x, movement.y, movement.z};
    NewtonBodySetForce(body, vec);
    
    // ###### rotation ######
    Vec3 rotation {0, 0, 0};
    if (actionStatus & ACTION_ROLL_CW)
        rotation += multiplyMatrixVec(makeModelMatrix(), rollSpeedUp);
    if (actionStatus & ACTION_ROLL_CCW)
        rotation -= multiplyMatrixVec(makeModelMatrix(), rollSpeedUp);

    if (actionStatus & ACTION_YAW_CW)
        rotation += multiplyMatrixVec(makeModelMatrix(), yawSpeedUp);
    if (actionStatus & ACTION_YAW_CCW)
        rotation -= multiplyMatrixVec(makeModelMatrix(), yawSpeedUp);

    if (actionStatus & ACTION_PITCH_UP)
        rotation += multiplyMatrixVec(makeModelMatrix(), pitchSpeedUp);
    if (actionStatus & ACTION_PITCH_DOWN)
        rotation -= multiplyMatrixVec(makeModelMatrix(), pitchSpeedUp);

    // use rotation vector on spaceship
    if (underControl){
        rotation = rotation + needToRotate;
    }
    float rot[3] {rotation.x, rotation.y, rotation.z};
    NewtonBodyAddTorque(body, rot);

    // ###### other ######
    if (actionStatus & ACTION_HANDING) {
        setHanding(0.9);
    }
    else setHanding(0.0);
}