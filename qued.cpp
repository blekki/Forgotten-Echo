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

void Qued::declareQued(Vec3 from, Vec3 to){
	float s = sqrt((1.0f + from.x * to.x + from.y * to.y + from.z * to.z) * 2.0f);
	if (s > 0.0f) {
		float is = 1.0f / s;
		this->x = (from.y * to.z - from.z * to.y) * is;
		this->y = (from.z * to.x - from.x * to.z) * is;
		this->z = (from.x * to.y - from.y * to.x) * is;
		this->w = s * 0.5f;
	}
	// else
	// {
	//     // Is this actually a problem?
	//     if (vector_equal(v1, kBasisZVector) || vector_equal(v0, kBasisZVector))
	//     {
	//         q = make_quaternion(0, 1, 0, 0);
	//     }
	//     else
	//     {
	//         q = kIdentityQuaternion;
	//     }
	//     // We arrive here for antiparallel vectors. Rotation axis is then undefined, but not rotating is
	//     // wrong. Probably the calling function should exclude this situation. For current
	//     // in-game use of this function we return (0,1,0,0), but generally that is also wrong.
	// }
}