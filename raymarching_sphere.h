#ifndef	_RAYMARCHINNG_SPHERE_H_
#define	_RAYMARCHINNG_SPHERE_H_

#include <cmath>

#include "vec.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "raymarching_object.h"

namespace edupt {

struct RaymarchingSphere : public RaymarchingObject {
public:
	RaymarchingSphere(const Color &emission, const Color &color, const ReflectionType reflection_type) : RaymarchingObject(emission, color, reflection_type) {
	}

	double distanceFunction(const Vec &position) const {
		return (position - Vec(77, 16.5, 78)).length() - 16.5;
	}
};
}

#endif
