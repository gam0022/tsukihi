#ifndef	_OBJECT_H_
#define	_OBJECT_H_

#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"

namespace tsukihi {

	struct Object {
	public:
		Color emission;
		Color color;
		ReflectionType reflection_type;

		Object() : emission(0), color(0), reflection_type(REFLECTION_TYPE_DIFFUSE) {}

		Object(const Color &emission, const Color &color, const ReflectionType reflection_type) :
			emission(emission), color(color), reflection_type(reflection_type) {
		}

		// 入力のrayに対する交差点までの距離を返す。交差しなかったら0を返す。
		// rayとの交差判定を行う。交差したらtrue,さもなくばfalseを返す。
		virtual bool intersect(const Ray& ray, Hitpoint* hitpoint) const {
			return false;
		}

		virtual double distanceFunction(const Vec3 &p) const {
			return 0.0;
		}
	};

};

#endif
