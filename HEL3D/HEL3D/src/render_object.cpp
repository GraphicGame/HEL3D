#include "render_object.h"
#include "render_pipeline.h"

render_object::render_object() {
	
}

render_object::~render_object() {
	
}

extern void simple_load_model(const char *path, render_object *ro);

HEL_API void render_object::load_model(const char *path) {
	simple_load_model(path, this);
}

HEL_API void render_object::add_vertex(point4d vert) {
	vlist_local_.push_back(vert);
	vlist_trans_.push_back(point4d());
}

HEL_API void render_object::draw(camera *cam, color_buffer *cb) {
	rpl_local_2_world(this);
	rpl_cull_invisible_object(this, cam);
	rpl_cull_backfaces(this, cam);
	rpl_world_2_camera(this, cam);
	rpl_camera_2_projective(this, cam);
	rpl_projective_2_screen(this, cam);
	rpl_rasterize(this, cb);
}

HEL_API render_object * render_create_object() {
	render_object *ro = new render_object();
	return ro;
}

HEL_API void render_release_object(render_object *ro) {
	delete ro;
}