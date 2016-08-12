#ifndef	_RAYMARCHINNG_SPHERE_H_
#define	_RAYMARCHINNG_SPHERE_H_

#include <cmath>

#include "vec3.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "raymarching_object.h"

namespace tukihi {

struct RaymarchingSphere : public RaymarchingObject {
public:
	RaymarchingSphere(const Color &emission, const Color &color, const ReflectionType reflection_type) : RaymarchingObject(emission, color, reflection_type) {
	}

	double distanceFunction(const Vec3 &position) const {
		return (position - Vec3(77, 16.5, 78)).length() - 16.5;
	}
};
}

#endif
