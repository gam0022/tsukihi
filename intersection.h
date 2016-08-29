#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include "math/vec3.h"
#include "constant.h"

namespace tsukihi {
	struct Object;

	struct Hitpoint {
		double distance;
		Vec3 normal;
		Vec3 position;

		Hitpoint() : distance(kINF), normal(), position() {}
	};

	struct Intersection {
		Hitpoint hitpoint;
		Object* object;

		Intersection() : object(nullptr) {}
	};
};

#endif
