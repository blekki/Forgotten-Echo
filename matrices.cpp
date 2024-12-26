#include <stdlib.h>

#include "matrices.h"

using namespace std;

// void rotMatrices::declareMatrix(Matrix4 matrix4, Qued qued){
void rotMatrices::declareMatrix(Matrix4* matrix4, Matrix4* opposMatrix4, Vec3 from, Vec3 to){
	Qued qued;

	Vec3 tinyToVec = from + (to - from) / 90.0f;
	tinyToVec.normalize();

    qued.newQued(from, tinyToVec);

	*matrix4 = rotationMatrix(qued);
	qued.conjugate();
	*opposMatrix4 = rotationMatrix(qued);

	// return rotationMatrix(qued);
}