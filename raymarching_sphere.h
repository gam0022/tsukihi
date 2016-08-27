#ifndef	_RAYMARCHINNG_SPHERE_H_
#define	_RAYMARCHINNG_SPHERE_H_

#include <cmath>

#include "vec3.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "raymarching_object.h"

namespace tsukihi {

	struct RaymarchingSphere : public RaymarchingObject {
	public:
		RaymarchingSphere(const Vec3 &position, const double scale, const Color &emission, const Color &color, const ReflectionType reflection_type) :
			RaymarchingObject(position, scale, emission, color, reflection_type) {
		}

		double distanceFunction(const Vec3 &p) const {
			return length(p - position) - scale;
		}
	};
}

#endif
