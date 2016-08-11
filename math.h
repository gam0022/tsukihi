#ifndef	_MATH_H_
#define	_MATH_H_

#include <cmath>
#include <algorithm>

namespace edupt {
	inline const double mod(double x, double y) {
		double a = std::fmod(x, y);
		return a > 0 ? a : a + y;
	}
};

#endif