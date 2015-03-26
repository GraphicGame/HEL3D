#ifndef camera_h
#define camera_h

#include "common_header.h"
#include "helmath.h"

enum camera_type {
	CAMERA_TYPE_EULER = 0,
	CAMERA_TYPE_UVN
};

class camera {
public:
	camera();
	virtual ~camera();
public:
	HEL_API point4d& pos();
	HEL_API const mat_4X4* get_mat_camera();
	HEL_API const mat_4X4* get_mat_perspective();
	HEL_API const mat_4X4* get_mat_screen();
	HEL_API float get_view_d_h();
	HEL_API float get_view_d_v();
	HEL_API float get_viewport_width();
	HEL_API float get_viewport_height();
	HEL_API virtual void build_matrix();
	HEL_API void __debug_load_config(const char *path);
protected:
	int state_;
	int attr_;
	point4d pos_;
	
	float view_d_h_;
	float view_d_v_;
	float fov_;
	float near_clip_z_;
	float far_clip_z_;

	plane3d clip_plane_left_;
	plane3d clip_plane_right_;
	plane3d clip_plane_top_;
	plane3d clip_plane_bottom_;

	float viewplane_width_;
	float viewplane_height_;
	float viewport_width_;
	float viewport_height_;
	float viewport_center_x_;
	float viewport_center_y_;
	float aspect_ratio_;

	mat_4X4 mat_camera_;
	mat_4X4 mat_perspective_;
	mat_4X4 mat_screen_;
};

class camera_euler : public camera {
public:
	camera_euler();
	~camera_euler();
public:
	HEL_API void setup_camera(point4d pos, vec4 angle,
		float near, float far, float fov,
		float viewport_width, float viewport_height);
	HEL_API void build_matrix() override;
private:
	vec4 euler_angle_;
};

//TODO...
class camera_uvn : public camera {
	
};

HEL_API camera_euler * render_create_camera_euler();
HEL_API void render_replease_camera_euler(camera_euler *cam);
HEL_API camera_uvn * render_create_camera_uvn();
HEL_API void render_replease_camera_uvn(camera_uvn *cam);

#endif