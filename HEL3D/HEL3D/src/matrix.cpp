#include "helmath.h"

#include <memory>

mat_4X4::mat_4X4() {
	identity();
}

mat_4X4::mat_4X4(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {
	
	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;
	this->m03 = m03;

	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;

	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;

	this->m30 = m30;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

void mat_4X4::identity() {
	memset(m, 0, sizeof(mat_4X4));
	m00 = 1;
	m11 = 1;
	m22 = 1;
	m33 = 1;
}

void mat_identity_4X4(mat_4X4 *m) {
	memset(m, 0, sizeof(mat_4X4));
	m->m00 = 1;
	m->m11 = 1;
	m->m22 = 1;
	m->m33 = 1;
}

void mat_mul_4X4(const mat_4X4 *ma, const mat_4X4 *mb, mat_4X4 *mr) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			float v = 0;
			for (int i = 0; i < 4; i++) {
				v += (ma->m[row][i] * mb->m[i][col]);
			}
			mr->m[row][col] = v;
		}
	}
}

void mat_mul_1X4_4X4(const vec4 *va, const mat_4X4 *mb, vec4 *vr) {
	vr->x = va->x * mb->m00 + va->y * mb->m10 + va->z * mb->m20 + mb->m30;
	vr->y = va->x * mb->m01 + va->y * mb->m11 + va->z * mb->m21 + mb->m31;
	vr->z = va->x * mb->m02 + va->y * mb->m12 + va->z * mb->m22 + mb->m32;
}

void mat_init_translation_matrix(mat_4X4 *m, float x, float y, float z) {
	m->m30 = x;
	m->m31 = y;
	m->m32 = z;
}