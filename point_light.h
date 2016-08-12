#ifndef	_POINT_LIGHT_H_
#define	_POINT_LIGHT_H_

#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "material.h"

namespace edupt {

	struct PointLight {
	public:
		Color emission;
		Vec3 position;

		PointLight(const Color &emission, const Vec3 &position) :
			emission(emission), position(position) {}
	};

};

#endif
