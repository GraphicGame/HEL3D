#ifndef render_object_h
#define render_object_h

#include <vector>
#include <string>

#include "common_header.h"
#include "helmath.h"

struct polygon;
struct polygon_independent;
struct render_polygon_list;

typedef struct render_object {
public:
	render_object();
	~render_object();

	HEL_API void load_model(const char *path);
	HEL_API void add_polygon();
	HEL_API int get_num_polys() const;
	HEL_API void gen_render_polygon_list(render_polygon_list *rpl);

	int id_;
	std::string name_;
	int state_;
	int attr_;
	float avg_radius_;
	float max_radius_;
	point4d world_pos_;
	vec4 dir_;
	vec4 ux_, uy_, uz_;

	std::vector<point4d> vlist_local_;
	std::vector<point4d> vlist_trans_;
	std::vector<polygon*> poly_list_;
} render_object;

typedef struct render_polygon_list {
	render_polygon_list();
	~render_polygon_list();

	int state_;
	int attr_;

	std::vector<polygon_independent> poly_list_;
} render_polygon_list;

typedef struct polygon {
	int state_;
	int attr_;
	int color_;

	std::vector<point4d> *vlist_ptr_;
	int vertex_index_[3];
} polygon;

typedef struct polygon_independent {
	point4d vlist_local_[3];
	point4d vlist_trans_[3];
} polygon_independent;

HEL_API render_object * render_create_object();
HEL_API void render_release_object(render_object *ro);

HEL_API render_polygon_list * render_create_polygonlist();
HEL_API void render_release_polygonlist(render_polygon_list *rpl);

#endif