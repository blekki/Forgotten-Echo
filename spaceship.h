#pragma once

#include "object.h"

#include "ForgottenEcho.h"
#include "shader/brightness.h"

class Spaceship: public Object
{   
    private:
        bool underControl;
        int currentActionStatus;
        
        Vec3 forwardSpeedUp;
        Vec3 rightSpeedUp;
        Vec3 upSpeedUp;
        
        Vec3 rollSpeedUp;
        Vec3 yawSpeedUp;
        Vec3 pitchSpeedUp;
        
        NewtonBody *body;

    public:
        void setControlStatus(bool status);
        void pushActionStatus(int status);
        void setNewtonBody(NewtonBody *body);
        void setSpeedUp(float forward, float right, float up);
        void setRotationSpeedUp(float roll, float yaw, float pitch);

        virtual float getX() override;
        virtual float getY() override;
        virtual float getZ() override;
        virtual xyz_t getXYZ() override;
        virtual Matrix4 makeModelMatrix() override;
        
        virtual void draw(Brightness &brightnessShader){
            if (body == 0){
                return;
            }
            Matrix4 bodyMatrix;
            NewtonBodyGetMatrix(body, bodyMatrix.ptr());
            Matrix4 scaleMatrix;
            scaleMatrix.ptr()[0] = scale;
            scaleMatrix.ptr()[5] = scale;
            scaleMatrix.ptr()[10] = scale;
            brightnessShader.setModelMatrix(multiplyMatrix(bodyMatrix, scaleMatrix));
            Object::draw();
        }

        void ApplyForceAndTorque();

        Spaceship(){
            underControl = false;
            body = 0;
        };
};