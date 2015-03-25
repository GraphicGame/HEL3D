#include "helmath.h"

void plane3d::init(point3d *p0, vec3 *n, bool normalize /* = true */) {
	this->p0.x = p0->x;
	this->p0.y = p0->y;
	this->p0.z = p0->z;

	this->n.x = n->x;
	this->n.y = n->y;
	this->n.z = n->z;

	if (normalize) {
		vec3_normalize(&this->n);
	}
}