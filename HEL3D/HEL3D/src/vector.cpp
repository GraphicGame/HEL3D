#include "helmath.h"

#include <math.h>

void vec2_add(vec2 *va, vec2 *vb, vec2 *vr) {
	vr->x = va->x + vb->x;
	vr->y = va->y + vb->y;
}

void vec3_add(vec3 *va, vec3 *vb, vec3 *vr) {
	vr->x = va->x + vb->x;
	vr->y = va->y + vb->y;
	vr->z = va->z + vb->z;
}

void vec4_add(vec4 *va, vec4 *vb, vec4 *vr) {
	vr->x = va->x + vb->x;
	vr->y = va->y + vb->y;
	vr->z = va->z + vb->z;
	vr->w = va->w + vb->w;
}

void vec2_sub(vec2 *va, vec2 *vb, vec2 *vr) {
	vr->x = va->x - vb->x;
	vr->y = va->y - vb->y;
}

void vec3_sub(vec3 *va, vec3 *vb, vec3 *vr) {
	vr->x = va->x - vb->x;
	vr->y = va->y - vb->y;
	vr->z = va->z - vb->z;
}

void vec4_sub(vec4 *va, vec4 *vb, vec4 *vr) {
	vr->x = va->x - vb->x;
	vr->y = va->y - vb->y;
	vr->z = va->z - vb->z;
	vr->w = va->w - vb->w;
}

void vec2_scale(vec2 *va, float k, vec2 *vr) {
	vr->x = va->x * k;
	vr->y = va->y * k;
}

void vec3_scale(vec3 *va, float k, vec3 *vr) {
	vr->x = va->x * k;
	vr->y = va->y * k;
	vr->z = va->z * k;
}

void vec4_scale(vec4 *va, float k, vec4 *vr) {
	vr->x = va->x * k;
	vr->y = va->y * k;
	vr->z = va->z * k;
	vr->w = va->w * k;
}

float vec2_dot(vec2 *va, vec2 *vb) {
	return va->x * vb->x + va->y * vb->y;
}

float vec3_dot(vec3 *va, vec3 *vb) {
	return va->x * vb->x + va->y * vb->y + va->z * vb->z;
}

float vec4_dot(vec4 *va, vec4 *vb) {
	return va->x * vb->x + va->y * vb->y + va->z * vb->z;
}

void vec3_cross(vec3 *va, vec3 *vb, vec3 *vr) {
	vr->x = va->y * vb->z - vb->y * va->z;
	vr->y = va->x * vb->z - vb->x * va->z;
	vr->z = va->x * vb->y - vb->x * va->y;
}

void vec4_cross(vec4 *va, vec4 *vb, vec4 *vr) {
	vr->x = va->y * vb->z - vb->y * va->z;
	vr->y = va->x * vb->z - vb->x * va->z;
	vr->z = va->x * vb->y - vb->x * va->y;
}

float vec2_len(vec2 *va) {
	return sqrtf(va->x * va->x + va->y * va->y);
}

float vec3_len(vec3 *va) {
	return sqrtf(va->x * va->x + va->y * va->y + va->z * va->z);
}

float vec4_len(vec4 *va) {
	return sqrtf(va->x * va->x + va->y * va->y + va->z * va->z + va->w * va->w);
}

void vec2_normalize(vec2 *va) {
	float len = vec2_len(va);
	va->x /= len;
	va->y /= len;
}

void vec3_normalize(vec3 *va) {
	float len = vec3_len(va);
	va->x /= len;
	va->y /= len;
	va->z /= len;
}

void vec4_normalize(vec4 *va) {
	float len = vec4_len(va);
	va->x /= len;
	va->y /= len;
	va->z /= len;
	va->w /= len;
}

void mat_mul_4X4(mat_4X4 *ma, mat_4X4 *mb, mat_4X4 *mr) {
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

void mat_mul_1X4_4X4(vec4 *va, mat_4X4 *mb, vec4 *vr) {
	vr->x = va->x * mb->m00 + va->y * mb->m10 + va->z * mb->m20 + mb->m30;
	vr->y = va->x * mb->m01 + va->y * mb->m11 + va->z * mb->m21 + mb->m31;
	vr->z = va->x * mb->m02 + va->y * mb->m12 + va->z * mb->m22 + mb->m32;
}