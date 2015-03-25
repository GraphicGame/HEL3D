#include "helmath.h"

#include <math.h>

vec2::vec2()
: x(0), y(0)
{
	
}

vec2::vec2(float x, float y)
: x(x), y(y)
{
	
}

vec3::vec3()
: x(0), y(0), z(0)
{

}

vec3::vec3(float x, float y, float z)
: x(x), y(y), z(z)
{

}

void vec3::init(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

vec4::vec4()
: x(0), y(0), z(0), w(1)
{

}

vec4::vec4(float x, float y, float z, float w)
: x(x), y(y), z(z), w(w)
{

}

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