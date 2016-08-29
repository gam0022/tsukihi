#ifndef	_RAYMARCHINNG_MBOX_H_
#define	_RAYMARCHINNG_MBOX_H_

#include <cmath>
#include <algorithm>

#include "math/vec3.h"
#include "math/vec4.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "object/raymarching_object.h"

namespace tsukihi {
	struct RaymarchingMbox : public RaymarchingObject {
	public:
		RaymarchingMbox(const Vec3 &position, const double scale, const Color &emission, const Color &color, const ReflectionType reflection_type) :
			RaymarchingObject(position, scale, emission, color, reflection_type) {
			kREP = 512;
			kREPS = 11e-3;
		}

		double kMBox = 3.0;

		inline double mbox(const Vec3& p) const {
			const int n = 12;
			Vec4 q0 = Vec4(p.x, p.y, p.z, 1.0);
			Vec4 q = q0;
			for (int i = 0; i < n; i++) {
				q.set_xyz(clamp(q.xyz(), -1.0, 1.0) * 2.0 - q.xyz());
				q = q * kMBox / clamp(dot(q.xyz(), q.xyz()), 0.5, 1.0) + q0;
			}
			return length(q.xyz()) / std::abs(q.w);
		}

		double distanceFunction(const Vec3 &p) const {
			return mbox((p - position) / scale) * scale;
		}
	};
}

#endif