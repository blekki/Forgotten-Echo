#include <stdlib.h>
#include <iostream>
#include <cmath>

#include "qued.h"

Matrix4 rotationMatrix(Qued qued){
	float w, wz, wy, wx;
	float x, xz, xy, xx;
	float y, yz, yy;
	float z, zz;
	
	Qued q = qued;
	q.normalize();
	
	w = q.w;
	z = q.z;
	y = q.y;
	x = q.x;
	
	xx = 2.0f * x; yy = 2.0f * y; zz = 2.0f * z;
	wx = w * xx; wy = w * yy; wz = w * zz;
	xx = x * xx; xy = x * yy; xz = x * zz;
	yy = y * yy; yz = y * zz;
	zz = z * zz;
	
    return Matrix4(
        1.0f - yy - zz,	xy + wz,		xz - wy,		0.0f,
		xy - wz,		1.0f - xx - zz,	yz + wx,		0.0f,
		xz + wy,		yz - wx,		1.0f - xx - yy,	0.0f,
		0.0f,			0.0f,			0.0f,			1.0f
	);
}

Matrix4 multiplyMatrix(Matrix4 matrix1, Matrix4 matrix2){
    Matrix4 out;
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            float sum = 0;
            for (int c = 0; c < 4; c++) {
                sum = sum + matrix1.at(a, c) * matrix2.at(c, b);
            }
            out.set(a, b, sum);
        }
    }

    return out;
}

void Qued::normalize(){
	float w = this->w;
	float x = this->x;
	float y = this->y;
	float z = this->z;
	
	float lv = 1.0f / sqrt(w*w + x*x + y*y + z*z);
	
	w = lv * w;
	x = lv * x;
	y = lv * y;
	z = lv * z;
}

void Qued::conjugate(){
	x = -x;
	y = -y;
	z = -z;
	//variable w not changed
}