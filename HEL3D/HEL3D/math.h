#ifndef math_h
#define math_h

typedef struct {
	union {
		struct {
			float x, y;
		};
		struct {
			float m0, m1;
		};
		float m[2];
	};
} vec2, mat_1X2;

typedef struct {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float m0, m1, m2;
		};
		float m[3];
	};
} vec3, mat_1X3;

typedef struct {
	union {
		struct {
			float x, y, z, w;
		};
		struct {
			float m0, m1, m2, m3;
		};
		float m[4];
	};
} vec4, mat_1X4;

//vector...
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

//matrix...
typedef struct {
	union {
		struct {
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[4][4];
	};
} mat_4X4;

void mat_mul_4X4(mat_4X4 *ma, mat_4X4 *mb, mat_4X4 *mr);
void mat_mul_1X4_4X4(vec4 *va, mat_4X4 *mb, vec4 *vr);

#endif