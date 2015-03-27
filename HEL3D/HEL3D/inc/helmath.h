#ifndef helmath_h
#define helmath_h

//vector...
typedef struct vec2 {
	union {
		struct {
			float x, y;
		};
		struct {
			float m0, m1;
		};
		float m[2];
	};
	vec2();
	vec2(float x, float y);
} vec2, mat_1X2, point2d;

typedef struct vec3 {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float m0, m1, m2;
		};
		float m[3];
	};
	vec3();
	vec3(float x, float y, float z);
	void init(float x, float y, float z);
} vec3, mat_1X3, point3d;

typedef struct vec4 {
	union {
		struct {
			float x, y, z, w;
		};
		struct {
			float m0, m1, m2, m3;
		};
		float m[4];
	};
	vec4();
	vec4(float x, float y, float z, float w);
	void copy(const vec4 *target);
} vec4, mat_1X4, point4d;

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

float vec2_angle(vec2 *va, vec2 *vb);
float vec3_angle(vec3 *va, vec3 *vb);
float vec4_angle(vec4 *va, vec4 *vb);

//matrix...
typedef struct mat_4X4 {
	union {
		struct {
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[4][4];
	};
	mat_4X4();
	mat_4X4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);
	void identity();
} mat_4X4;

void mat_identity_4X4(mat_4X4 *m);
void mat_mul_4X4(const mat_4X4 *ma, const mat_4X4 *mb, mat_4X4 *mr);
void mat_mul_1X4_4X4(const vec4 *va, const mat_4X4 *mb, vec4 *vr);
void mat_init_translation_matrix(mat_4X4 *m, float x, float y, float z);

//plane.
typedef struct plane3d {
	point3d p0;
	vec3 n;

	void init(point3d *p0, vec3 *n, bool normalize = true);
} plane3d;

#endif