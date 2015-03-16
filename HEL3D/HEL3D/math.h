#ifndef math_h
#define math_h

//vectors.
typedef struct vector2d {
	float x, y;
} vec2;

typedef struct vector3d {
	float x, y, z;
} vec3;

typedef struct vector4d {
	float x, y, z, w;
} vec4;

void vec2_add(vec2 *va, vec2 *vb, vec2 *vr);
void vec3_add(vec3 *va, vec3 *vb, vec3 *vr);
void vec4_add(vec4 *va, vec4 *vb, vec4 *vr);

void vec2_sub(vec2 *va, vec2 *vb, vec2 *vr);
void vec3_sub(vec3 *va, vec3 *vb, vec3 *vr);
void vec4_sub(vec4 *va, vec4 *vb, vec4 *vr);

void vec2_scale(vec2 *va, float k, vec2 *vr);
void vec3_scale(vec3 *va, float k, vec3 *vr);
void vec4_scale(vec4 *va, float k, vec4 *vr);

float vec2_dot(vec2 *va, vec2 *vb);
float vec3_dot(vec3 *va, vec3 *vb);
float vec4_dot(vec4 *va, vec4 *vb);

void vec3_cross(vec3 *va, vec3 *vb, vec3 *vr);
void vec4_cross(vec4 *va, vec4 *vb, vec4 *vr);

float vec2_len(vec2 *va);
float vec3_len(vec3 *va);
float vec4_len(vec4 *va);

void vec2_normalize(vec2 *va);
void vec3_normalize(vec3 *va);
void vec4_normalize(vec4 *va);

//matrix
//TODO

#endif