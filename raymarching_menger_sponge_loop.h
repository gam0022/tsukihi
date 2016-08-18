#ifndef	_RAYMARCHINNG_MENGER_SPONGE_LOOP_H_
#define	_RAYMARCHINNG_MENGER_SPONGE_LOOP_H_

#include <cmath>
#include <algorithm>

#include "raymarching_menger_sponge.h"

namespace tukihi {

	struct RaymarchingMengerSpongeLoop : public RaymarchingMengerSponge {
	public:
		RaymarchingMengerSpongeLoop(const Vec3 &position, const double scale, const Color &emission, const Color &color, const ReflectionType reflection_type) :
			RaymarchingMengerSponge(position, scale, emission, color, reflection_type) {
		}

		const double mengerSpongeLoop(const Vec3& p) const {
			double d = 0.0;
			const double one_third = 1.0 / 3.0;
			for (int i = 0; i < 4; i++) {
				double k = pow(one_third, i);
				double kh = k * 0.5;
				d = std::max(d, -crossBar(mod(p + kh, k * 2.0) - kh, k * one_third));
			}
			return d;
		}

		double distanceFunction(const Vec3 &p) const {
			return mengerSpongeLoop((p - position) / scale) * scale;
		}
	};
}

#endif