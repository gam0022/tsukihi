#ifndef	_POINT_LIGHT_H_
#define	_POINT_LIGHT_H_

#include <cmath>

#include "math/vec3.h"
#include "ray.h"
#include "material.h"
#include "object/object.h"

namespace tsukihi {

	struct PointLight : public Sphere {
	public:
		PointLight(const double radius, const Vec3 &position, const Color &emission) :
			Sphere(radius, position, emission, emission, REFLECTION_TYPE_DIFFUSE) {}
	};

};

#endif
