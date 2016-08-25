#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

namespace tsukihi {

struct Ray {
	Vec3 org, dir;
	Ray(const Vec3 &org, const Vec3 &dir) : org(org), dir(dir) {}
};

};

#endif
