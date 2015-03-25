#ifndef render_pipeline_h
#define render_pipeline_h

#include "render_object.h"

void rpl_local_2_world(render_object *ro);
void rpl_cull_invisible_object(render_object *ro);
void rpl_cull_backfaces(render_object *ro);
void rpl_world_2_camera(render_object *ro);
void rpl_camera_2_projective(render_object *ro);
void rpl_projective_2_screen(render_object *ro);

#endif