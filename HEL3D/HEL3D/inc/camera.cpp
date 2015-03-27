#include "camera.h"
#include "utils.h"
#include "helmath.h"
#include "render_object.h"
#include "log_internal.h"

#include <math.h>
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

camera::camera() {
	
}

camera::~camera() {
	
}

HEL_API point4d& camera::pos() {
	return pos_;
}

HEL_API const mat_4X4 * camera::get_mat_camera() {
	return &mat_camera_;
}

HEL_API const mat_4X4 * camera::get_mat_perspective() {
	return &mat_perspective_;
}

HEL_API const mat_4X4 * camera::get_mat_screen() {
	return &mat_screen_;
}

HEL_API float camera::get_view_d_h() {
	return view_d_h_;
}

HEL_API float camera::get_view_d_v() {
	return view_d_v_;
}

HEL_API float camera::get_viewport_width() {
	return viewport_width_;
}

HEL_API float camera::get_viewport_height() {
	return viewport_height_;
}

HEL_API void camera::build_matrix() {
	assert(false);
}

camera_euler::camera_euler()
:target_(nullptr) {
	
}

camera_euler::~camera_euler() {
	
}

HEL_API void camera_euler::setup_camera(point4d pos, vec4 angle, 
	float near, float far, float fov, 
	float viewport_width, float viewport_height) {
	pos_ = pos;
	euler_angle_ = angle;
	near_clip_z_ = near;
	far_clip_z_ = far;
	fov_ = fov;
	viewport_width_ = viewport_width;
	viewport_height_ = viewport_height;
	viewport_center_x_ = (viewport_width_ - 1) / 2;
	viewport_center_y_ = (viewport_height_ - 1) / 2;
	aspect_ratio_ = viewport_width_ / viewport_height_;

	viewplane_width_ = 2.0f;
	viewplane_height_ = 2.0f / aspect_ratio_;

	view_d_h_ = view_d_v_ = 0.5f * viewplane_width_ * tan(deg_2_rad(fov_ / 2));

	//assume fov is 90бу
	point3d p0;
	vec3 vn;

	vn.init(-1, 0, -1);
	clip_plane_left_.init(&p0, &vn);

	vn.init(1, 0, -1);
	clip_plane_right_.init(&p0, &vn);

	vn.init(0, 1, -1);
	clip_plane_top_.init(&p0, &vn);

	vn.init(0, -1, -1);
	clip_plane_bottom_.init(&p0, &vn);
}

HEL_API void camera_euler::build_matrix() {
	mat_4X4 mat_translation;
	mat_init_translation_matrix(&mat_translation, -pos_.x, -pos_.y, -pos_.z);
	
	if (target_ != nullptr) {
		float vx = target_->world_pos_.x - pos_.x;
		float vy = target_->world_pos_.y - pos_.y;
		float vz = target_->world_pos_.z - pos_.z;

		vec2 v2xz1(0, 1);
		vec2 v2xz2(vx, vz);
		float deg = vec2_angle(&v2xz1, &v2xz2);
		euler_angle_.y = deg;

		//log_print("deg=%f\n", {arg(deg)});
	}

	//YXZ-rotation.
	mat_4X4 mat_rotation;
	float euler_x = deg_2_rad(euler_angle_.x);
	float euler_y = deg_2_rad(euler_angle_.y);
	float euler_z = deg_2_rad(euler_angle_.z);

	mat_4X4 mat_x_rotation = {
		1, 0, 0, 0,
		0, cos(euler_x), -sin(euler_x), 0,
		0, sin(euler_x), cos(euler_x), 0, 
		0, 0, 0, 1
	};

	mat_4X4 mat_y_rotation = {
		cos(euler_y), 0, sin(euler_y), 0,
		0, 1, 0, 0,
		-sin(euler_y), 0, cos(euler_y), 0,
		0, 0, 0, 1
	};

	mat_4X4 mat_z_rotation = {
		cos(euler_z), -sin(euler_z), 0, 0,
		sin(euler_z), cos(euler_z), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	mat_4X4 mat_temp;
	mat_mul_4X4(&mat_y_rotation, &mat_x_rotation, &mat_temp);
	mat_mul_4X4(&mat_temp, &mat_z_rotation, &mat_rotation);
	mat_mul_4X4(&mat_translation, &mat_rotation, &mat_camera_);
}

HEL_API const vec4 * camera_euler::get_euler_angle() {
	return &euler_angle_;
}

HEL_API void camera_euler::set_target(const render_object *ro) {
	target_ = ro;
}

//for test...
HEL_API void camera::__debug_load_config(const char *path) {
	ifstream file(path);
	string line;
	getline(file, line);
	file.close();

	vector<string> tokens;
	bool inword = false;
	string token;
	for (int i = 0; i < line.size(); i++) {
		char c = line[i];
		if (c == ' ' || c == '\t' || c== '\n') {
			if (inword) {
				inword = false;
				tokens.push_back(token);
				token.clear();
			}
		}
		else {
			inword = true;
			token += c;
		}
	}
	if (token.size() != 0) {
		tokens.push_back(token);
	}
	if (tokens.size() == 3) {
		pos_.x = atof(tokens[0].c_str());
		pos_.y = atof(tokens[1].c_str());
		pos_.z = atof(tokens[2].c_str());
		pos_.w = 1;
	}
}

HEL_API camera_euler * render_create_camera_euler() {
	camera_euler *cam = new camera_euler();
	return cam;
}

HEL_API void render_replease_camera_euler(camera_euler *cam) {
	delete cam;
}

HEL_API camera_uvn * render_create_camera_uvn() {
	camera_uvn *cam = new camera_uvn();
	return cam;
}

HEL_API void render_replease_camera_uvn(camera_uvn *cam) {
	delete cam;
}