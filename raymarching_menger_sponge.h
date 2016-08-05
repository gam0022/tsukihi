#ifndef	_RAYMARCHINNG_MENGER_SPONGE_H_
#define	_RAYMARCHINNG_MENGER_SPONGE_H_

#include <cmath>
#include <algorithm>

#include "vec.h"
#include "vec2.h"
#include "material.h"
#include "constant.h"
#include "intersection.h"
#include "raymarching_object.h"

namespace edupt {

	struct RaymarchingMengerSponge : public RaymarchingObject {
	public:
		RaymarchingMengerSponge(const Color &emission, const Color &color, const ReflectionType reflection_type) : RaymarchingObject(emission, color, reflection_type) {
		}

		double box(Vec p, Vec b) const{
			Vec d = abs(p) - b;
			return std::min(std::max(d.x, std::max(d.y, d.z)), 0.0) + max(d, 0.0).length();
		}

		double box(Vec p, double b) const {
			return box(p, Vec(b, b, b));
		}

		double bar(Vec2 p, Vec2 b) const {
			Vec2 d = abs(p) - b;
			return std::min(std::max(d.x, d.y), 0.0) + max(d, 0.0).length();
		}

		double crossBar(Vec p, double b) const {
			double da = bar(p.xy(), Vec2(b, b)),
				db = bar(p.yz(), Vec2(b, b)),
				dc = bar(p.zx(), Vec2(b, b));
			return std::min(da, std::min(db, dc));
		}

		double distFunc(Vec p) const {
			double ret = box(p, 0.3);
			for (double c = 0.0; c < 4.0; c += 1.0){
				double pw = pow(3.0, c);
				ret = std::max(ret, -crossBar(mod(p + 0.15 / pw, 0.6 / pw) - 0.15 / pw, 0.1 / pw));
			}
			return ret;
		}

		double distanceFunction(const Vec &position) const {
			double scale = 70.0;
			auto center = Vec(50, 30, 78);
			return distFunc((position - center) / scale ) * scale;
		}
	};
}

#endif