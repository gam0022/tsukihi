#ifndef	_RAYMARCHINNG_MBOX_H_
#define	_RAYMARCHINNG_MBOX_H_

#include <cmath>
#include <algorithm>

#include "vec3.h"
#include "vec4.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "raymarching_object.h"

namespace tukihi {

	struct RaymarchingMbox : public RaymarchingObject {
	public:
		RaymarchingMbox(const Color &emission, const Color &color, const ReflectionType reflection_type) : RaymarchingObject(emission, color, reflection_type) {
			kREP = 512;
			kREPS = 1e-1;
		}

		double mboxScale = 2.2;

		inline double distFunc(Vec3 p) const {
			const int n = 12;
			Vec4 q0 = Vec4(p.x, p.y, p.z, 1.0);
			Vec4 q = q0;
			for (int i = 0; i < n; i++) {
				q.set_xyz(clamp(q.xyz(), -1.0, 1.0) * 2.0 - q.xyz());
				q = q * mboxScale / clamp(dot(q.xyz(), q.xyz()), 0.5, 1.0) + q0;
			}
			return length(q.xyz()) / std::abs(q.w);
		}

		double distanceFunction(const Vec3 &position) const {
			double scale = 5.0;
			auto center = Vec3(50, 30, 70);
			return distFunc((position - center) / scale) * scale;
		}
	};
}

#endif