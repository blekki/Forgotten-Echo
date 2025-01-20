#pragma once

struct xyz_t{
    float x;
    float y;
    float z;
    
    xyz_t(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    xyz_t(){
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    xyz_t& operator+(const xyz_t other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    xyz_t& operator-(const xyz_t other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    xyz_t& operator+=(const xyz_t other){
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    xyz_t& operator-=(const xyz_t other){
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
};