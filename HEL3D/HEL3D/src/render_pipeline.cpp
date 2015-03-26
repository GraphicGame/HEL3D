#include "render_pipeline.h"
#include "helmath.h"

void rpl_local_2_world(render_object *ro) {
	mat_4X4 mat;
	mat_identity_4X4(&mat);
	mat_init_translation_matrix(&mat, ro->world_pos_.x,
		ro->world_pos_.y, ro->world_pos_.z);
	for (int i = 0; i < ro->vlist_local_.size(); i++) {
		point4d vert = ro->vlist_local_[i];
		mat_mul_1X4_4X4(&vert, &mat, &ro->vlist_trans_[i]);
	}
}

//TODO
void rpl_cull_invisible_object(render_object *ro, camera *cam) {
	
}

//TODO
void rpl_cull_backfaces(render_object *ro, camera *cam) {
	
}

void rpl_world_2_camera(render_object *ro, camera *cam) {
	cam->build_matrix();
	for (int i = 0; i < ro->vlist_trans_.size(); i++) {
		point4d vert = ro->vlist_trans_[i];
		mat_mul_1X4_4X4(&vert, cam->get_mat_camera(), &ro->vlist_trans_[i]);
	}
}

void rpl_camera_2_projective(render_object *ro, camera *cam) {
	for (int i = 0; i < ro->vlist_trans_.size(); i++) {
		point4d *vert = &ro->vlist_trans_[i];
		float z = vert->z;
		float vdh = cam->get_view_d_h();
		float vdv = cam->get_view_d_v();
		vert->x = vdh * vert->x / z;
		vert->y = vdv * vert->y / z;
	}
}

void rpl_projective_2_screen(render_object *ro, camera *cam) {
	float vpw = cam->get_viewport_width();
	float vph = cam->get_viewport_height();
	float a = 0.5 * vpw - 0.5;
	float b = 0.5 * vph - 0.5;
	for (int i = 0; i < ro->vlist_trans_.size(); i++) {
		point4d *vert = &ro->vlist_trans_[i];
		vert->x = a + a * vert->x;
		vert->y = b - b * vert->y;
	}
}

void rpl_rasterize(render_object *ro, color_buffer *cb) {
	color c(0, 0, 255, 255);
	for (int i = 0; i < ro->poly_list_.size(); i++) {
		polygon *poly = ro->poly_list_[i];
		int *vert_index = poly->vertex_index_;
		point4d vert1 = ro->vlist_trans_[vert_index[0]];
		point4d vert2 = ro->vlist_trans_[vert_index[1]];
		point4d vert3 = ro->vlist_trans_[vert_index[2]];
		device_draw_line(cb, vert1.x, vert1.y, vert2.x, vert2.y, c);
		device_draw_line(cb, vert2.x, vert2.y, vert3.x, vert3.y, c);
		device_draw_line(cb, vert3.x, vert3.y, vert1.x, vert1.y, c);
	}
}