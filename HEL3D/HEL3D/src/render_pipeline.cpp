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
void rpl_cull_invisible_object(render_object *ro) {
	
}

//TODO
void rpl_cull_backfaces(render_object *ro) {
	
}