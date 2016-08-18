#ifndef	_RAYMARCHINNG_MENGER_SPONGE_H_
#define	_RAYMARCHINNG_MENGER_SPONGE_H_

#include <cmath>
#include <algorithm>

#include "vec3.h"
#include "vec2.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "raymarching_object.h"

namespace tukihi {

	struct RaymarchingMengerSponge : public RaymarchingObject {
	public:
		RaymarchingMengerSponge(const Color &emission, const Color &color, const ReflectionType reflection_type) : RaymarchingObject(emission, color, reflection_type) {
		}

		inline double box(Vec3 p, double x) const {
			//Vec d = abs(p) - x;
			//return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0) + max(d, 0.0).length();
			return max(abs(p) - x, 0.0).length();
		}

		inline double bar(Vec2 p, double x) const {
			Vec2 d = abs(p) - x;
			return std::min(std::max(d.x, d.y), 0.0) + max(d, 0.0).length();
			//return max(abs(p) - x, 0.0).length();
		}

		inline double crossBar(Vec3 p, double x) const {
			double bar_x = bar(p.yz(), x);
			double bar_y = bar(p.zx(), x);
			double bar_z = bar(p.xy(), x);
			return std::min(bar_z, std::min(bar_x, bar_y));
		}

		inline Vec3 opRep(Vec3 p, double interval) const {
			return mod(p, interval) - interval * 0.5;
		}

		inline double distFunc(Vec3 p) const {
			double d = box(p, 1.0);
			const double one_third = 1.0 / 3.0;
			for (int i = 0; i < 4; i++) {
				double k = pow(one_third, i);
				double kh = k * 0.5;
				d = std::max(d, -crossBar(mod(p + kh, k * 2.0) - kh, k * one_third));
			}
			return d;
		}

		double distanceFunction(const Vec3 &position) const {
			double scale = 22;
			auto center = Vec3(50, scale, 70);
			return distFunc((position - center) / scale) * scale;
		}
	};
}

#endif
